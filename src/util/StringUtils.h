#ifndef __Serveur__StringUtils__
#define __Serveur__StringUtils__

#include "Types.h"

#include <sstream>

namespace StringUtils {

    template <typename T>
    T fromString(const string_t &str) {
        T n;
        std::istringstream iss(str);
        iss >> n;
        return n;
    }

    template < typename T >
    string_t toString(const T &value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
}

#endif /* defined(__Serveur__StringUtils__) */
