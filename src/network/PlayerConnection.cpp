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
        ubyte_t buffer[BUFFER_SIZE];
        size_t position = 0;
        while (!closed) {
            size_t rcvd = socket->receive(buffer, sizeof(buffer));
            readBuffer.setPosition(readBuffer.getLimit());
            readBuffer.put(buffer, rcvd);
            readBuffer.setPosition(position);
            try {
                while (readBuffer.getPosition() < readBuffer.getLimit()) {
                    varint_t packetLength;
                    readBuffer.getVarInt(packetLength);
                    if (readBuffer.getLimit() - readBuffer.getPosition() < packetLength)
                        break;
                    varint_t packetId;
                    readBuffer.getVarInt(packetId);
                    ClientPacket *packet = nullptr;
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
                    Logger(LogLevel::DEBUG) << "/" << socket->getIP() << ":" << socket->getPort()
                        << " a envoyé un paquet " << typeid(*packet).name() << std::endl;
                    readQueue.push(packet);
                    if (readBuffer.getPosition() == readBuffer.getLimit())
                        readBuffer.clear();
                    position = readBuffer.getPosition();
                }
            } catch (const ByteBuffer::BufferUnderflowException &e) {}
        }
    } catch (const ClientSocket::SocketReadException &e) {
        Logger() << "/" << socket->getIP() << ":" << socket->getPort() << " s'est déconnecté" << std::endl;
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
            Logger(LogLevel::DEBUG) << "/" << socket->getIP() << ":" << socket->getPort()
                << " a reçu un paquet " << typeid(*packet).name() << std::endl;
            writeBuffer.clear();
            writeBuffer.setPosition(5);
            writeBuffer.putVarInt(packet->getPacketId());
            packet->write(writeBuffer);
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
            writeBuffer.setPosition(position);
            socket->transmit(writeBuffer.getArray() + position, writeBuffer.getLimit() - position);
            if ((phase == LOGIN && packet->getPacketId() == 0x00)
                    || (phase == PLAY && packet->getPacketId() == 0x40))
                close();
            else if (phase == PLAY && packet->getPacketId() == 0x00)
                sentKeepAlive = Clock::now();
            delete packet;
        }
    } catch (const ClientSocket::SocketWriteException &e) {
        Logger() << "/" << socket->getIP() << ":" << socket->getPort() << " s'est déconnecté" << std::endl;
        close();
    }
}
