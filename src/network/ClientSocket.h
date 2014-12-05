#ifndef __Serveur__ClientSocket__
#define __Serveur__ClientSocket__

#include "Socket.h"

class ClientSocket : public Socket {
public:
    struct SocketConnectException : public SocketException {
        SocketConnectException(int code) : SocketException(code) {}
    };

    struct SocketReadException : public SocketException {
        SocketReadException(int code) : SocketException(code) {}
    };

    struct SocketWriteException : public SocketException {
        SocketWriteException(int code) : SocketException(code) {}
    };

    ClientSocket(SocketAddress);

    ClientSocket(int, SocketAddress);

    ~ClientSocket();

    virtual void open();

    virtual size_t transmit(ubyte_t*, size_t);

    virtual size_t receive(ubyte_t*, size_t);

    string_t getIP();

    ushort_t getPort();

private:
    ubyte_t readBuffer[4096];
    ubyte_t* readPointer;
    int dataLength;
};

#endif /* defined(__Serveur__ClientSocket__) */
