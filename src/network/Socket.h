#ifndef __Serveur__Socket__
#define __Serveur__Socket__

#include "Types.h"

#include <cstring>
#include <stdexcept>
#include <netinet/in.h>
#include <cstring>

#define INVALID_HANDLE -1

#ifndef MSG_NOSIGNAL
const int MSG_NOSIGNAL = 0;
#endif

#ifndef SO_NOSIGPIPE
const int SO_NOSIGPIPE = 0;
#endif

class Socket {
public:
    class SocketAddress {
    public:
        SocketAddress(string_t ip, ushort_t port);

        string_t getIP();

        ushort_t getPort();

        struct sockaddr *getAddress();

        socklen_t getSize();

    private:
        sockaddr_in address;
    };

    struct SocketException : public std::runtime_error {
        SocketException(int code) : std::runtime_error(std::strerror(code)) {}
    };

    struct SocketCloseException : public SocketException {
        SocketCloseException(int code) : SocketException(code) {}
    };

    struct SocketCreateException : public SocketException {
        SocketCreateException(int code) : SocketException(code) {}
    };

    struct SocketFcntlException : public SocketException {
        SocketFcntlException(int code) : SocketException(code) {}
    };

    Socket(SocketAddress);

    virtual ~Socket();

    virtual void open() = 0;

    bool isOpen();

    void close();

protected:
    SocketAddress address;
    int handle;
    bool opened;
};

#endif /* defined(__Serveur__Socket__) */
