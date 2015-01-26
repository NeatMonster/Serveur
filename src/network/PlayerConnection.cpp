#include "PlayerConnection.h"

#include "ChatMessage.h"
#include "ClientPacket.h"
#include "ClientSocket.h"
#include "EntityPlayer.h"
#include "PacketDisconnect.h"
#include "PacketHandler.h"
#include "PacketHandshake.h"
#include "PacketLoginStart.h"
#include "PacketQueue.cpp"
#include "ServerPacket.h"
#include "Logger.h"

PlayerConnection::PlayerConnection(ClientSocket *socket) : socket(socket),
        closed(false), phase(HANDSHAKE), profile(nullptr), ping(0) {
    handler = new PacketHandler(this);
    readThread = std::thread(&PlayerConnection::runRead, this);
    writeThread = std::thread(&PlayerConnection::runWrite, this);
    sentKeepAlive = rcvdKeepAlive = Clock::now();
}

PlayerConnection::~PlayerConnection() {
    if (!player.expired())
        player.lock()->setDead();
    if (profile != nullptr)
        delete profile;
    delete handler;
    delete socket;
}

void PlayerConnection::join() {
    readThread.join();
    writeThread.join();
}

void PlayerConnection::close() {
    if (!closed) {
        closed = true;
        try {
            socket->close();
        } catch (const Socket::SocketCloseException &e) {}
        writeQueue.wake();
    }
}

bool PlayerConnection::isClosed() {
    return closed;
}

Profile *PlayerConnection::getProfile() {
    return profile;
}

string_t PlayerConnection::getIP() {
    return socket->getIP();
}

ushort_t PlayerConnection::getPort() {
    return socket->getPort();
}

float_t PlayerConnection::getPing() {
    return ping;
}

void PlayerConnection::handlePackets() {
    std::shared_ptr<ClientPacket> packet;
    while (!closed && readQueue.tryPop(packet))
        packet->handle(handler);
}

void PlayerConnection::sendPacket(std::shared_ptr<ServerPacket> packet) {
    if (!closed)
        writeQueue.push(packet);
}

void PlayerConnection::disconnect(string_t reason) {
    sendPacket(std::make_shared<PacketDisconnect>(phase == PLAY, (Chat() << reason).getJSON()));
}

PacketFactory PlayerConnection::factory;

string_t PlayerConnection::getName() {
    if (profile == nullptr)
        return "/" + socket->getIP() + ":" + std::to_string(socket->getPort());
    return profile->getName();
}

void PlayerConnection::runRead() {
    try {
        size_t position = 0;
        while (!closed) {
            readBuffer.reserve(readBuffer.getLimit() + BUFFER_SIZE);
            size_t rcvd = socket->receive(readBuffer.getArray() + readBuffer.getLimit(), BUFFER_SIZE);
            readBuffer.setLimit(readBuffer.getLimit() + rcvd);
            readBuffer.setPosition(position);
            std::shared_ptr<ClientPacket> packet;
            try {
                while (readBuffer.getPosition() < readBuffer.getLimit()) {
                    varint_t packetLength;
                    readBuffer.getVarInt(packetLength);
                    if (readBuffer.getLimit() - readBuffer.getPosition() < packetLength)
                        break;
                    varint_t packetId;
                    readBuffer.getVarInt(packetId);
                    packet = nullptr;
                    if (phase == HANDSHAKE && packetId == 0x00) {
                        packet = std::make_shared<PacketHandshake>();
                        phase = LOGIN;
                    } else if (phase == LOGIN && packetId == 0x00)
                        packet = std::make_shared<PacketLoginStart>();
                    else if (phase == PLAY && factory.hasPacket(packetId))
                        packet = factory.createPacket(packetId);
                    else {
                        disconnect("ID de paquet invalide : " + std::to_string(packetId));
                        break;
                    }
                    packet->setLength(packetLength);
                    packet->read(readBuffer);
                    Logger(LogLevel::DEBUG) << "<" << getName() << " -> Serveur> " << typeid(*packet).name() << std::endl;
                    readQueue.push(packet);
                    if (readBuffer.getPosition() == readBuffer.getLimit())
                        readBuffer.clear();
                    position = readBuffer.getPosition();
                }
            } catch (const PacketBuffer::BufferUnderflowException &e) {}
        }
    } catch (const ClientSocket::SocketReadException &e) {
        Logger() << "<" << getName() << " <-> Serveur> s'est déconnecté" << std::endl;
        close();
    }
}

void PlayerConnection::runWrite() {
    try {
        std::shared_ptr<ServerPacket> packet;
        while (!closed) {
            writeQueue.pop(packet);
            if (closed)
                break;
            Logger(LogLevel::DEBUG) << "<" << getName() << " <- Serveur> " << typeid(*packet).name() << std::endl;
            writeBuffer.clear();
            writeBuffer.setPosition(5);
            varint_t packetId = packet->getPacketId();
            writeBuffer.putVarInt(packetId);
            packet->write(writeBuffer);
            varint_t packetLength = writeBuffer.getLimit() - 5;
            if (packetLength < 128)
                writeBuffer.setMark(4);
            else if (packetLength < 16384)
                writeBuffer.setMark(3);
            else if (packetLength < 2097152)
                writeBuffer.setMark(2);
            else if (packetLength < 268435456)
                writeBuffer.setMark(1);
            else
                writeBuffer.setMark(0);
            writeBuffer.setPosition(writeBuffer.getMark());
            writeBuffer.putVarInt(packetLength);
            socket->transmit(writeBuffer.getArray() + writeBuffer.getMark(), writeBuffer.getLimit() - writeBuffer.getMark());
            if ((phase == LOGIN && packetId == 0x00) || (phase == PLAY && packetId == 0x40))
                close();
            else if (phase == PLAY && packetId == 0x00)
                sentKeepAlive = Clock::now();
        }
    } catch (const ClientSocket::SocketWriteException &e) {
        Logger() << "<" << getName() << " <-> Serveur> s'est déconnecté" << std::endl;
        close();
    }
}
