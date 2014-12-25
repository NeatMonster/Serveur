#include "PlayerConnection.h"

#include "ChatMessage.h"
#include "ClientPacket.h"
#include "ClientSocket.h"
#include "PacketDisconnect.h"
#include "PacketHandler.h"
#include "PacketHandshake.h"
#include "PacketLoginStart.h"
#include "PacketQueue.cpp"
#include "Player.h"
#include "ServerPacket.h"
#include "Logger.h"

PlayerConnection::PlayerConnection(ClientSocket *socket) : socket(socket),
        closed(false), phase(HANDSHAKE), player(nullptr), ping(0) {
    handler = new PacketHandler(this);
    readThread = std::thread(&PlayerConnection::runRead, this);
    writeThread = std::thread(&PlayerConnection::runWrite, this);
    sentKeepAlive = rcvdKeepAlive = Clock::now();
}

PlayerConnection::~PlayerConnection() {
    if (player != nullptr)
        delete player;
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

string_t PlayerConnection::getName() {
    if (handler->name.empty())
        return "/" + socket->getIP() + ":" + std::to_string(socket->getPort());
    return handler->name;
}

string_t PlayerConnection::getUUID() {
    return handler->uuid;
}

string_t PlayerConnection::getIP() {
    return socket->getIP();
}

ushort PlayerConnection::getPort() {
    return socket->getPort();
}

float_t PlayerConnection::getPing() {
    return ping;
}

void PlayerConnection::handlePackets() {
    ClientPacket *packet;
    while (!closed && readQueue.tryPop(packet)) {
        packet->handle(handler);
        delete packet;
    }
}

void PlayerConnection::sendPacket(ServerPacket *packet) {
    if (!closed)
        writeQueue.push(packet);
}

void PlayerConnection::disconnect(string_t reason) {
    sendPacket(new PacketDisconnect(phase == PLAY, (Chat() << reason).getJSON()));
}

PacketFactory PlayerConnection::factory;

void PlayerConnection::runRead() {
    try {
        size_t position = 0;
        while (!closed) {
            readBuffer.reserve(readBuffer.getLimit() + BUFFER_SIZE);
            size_t rcvd = socket->receive(readBuffer.getArray() + readBuffer.getLimit(), BUFFER_SIZE);
            readBuffer.setLimit(readBuffer.getLimit() + rcvd);
            readBuffer.setPosition(position);
            ClientPacket *packet = nullptr;
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
                        packet = new PacketHandshake();
                        phase = LOGIN;
                    } else if (phase == LOGIN && packetId == 0x00)
                        packet = new PacketLoginStart();
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
            } catch (const ByteBuffer::BufferUnderflowException &e) {
                if (packet != nullptr)
                    delete packet;
            }
        }
    } catch (const ClientSocket::SocketReadException &e) {
        Logger() << "<" << getName() << " <-> Serveur> s'est déconnecté" << std::endl;
        close();
    }
}

void PlayerConnection::runWrite() {
    try {
        ServerPacket *packet;
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
            delete packet;
            varint_t packetLength = writeBuffer.getLimit() - 5;
            size_t position = 0;
            if (packetLength < 128)
                position = 4;
            else if (packetLength < 16384)
                position = 3;
            else if (packetLength < 2097152)
                position = 2;
            else if (packetLength < 268435456)
                position = 1;
            writeBuffer.setPosition(position);
            writeBuffer.putVarInt(packetLength);
            socket->transmit(writeBuffer.getArray() + position, writeBuffer.getLimit() - position);
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
