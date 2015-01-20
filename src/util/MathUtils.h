#ifndef __Serveur__MathUtils__
#define __Serveur__MathUtils__

#include "Types.h"

namespace MathUtils {

    template<class T>
    inline T abs(T x) {
        return x > 0 ? -x : x;
    }

    template<class T>
    inline T min(T x, T y) {
        return x > y ? y : x;
    }

    template<class T>
    inline T max(T x, T y) {
        return x > y ? x : y;
    }

    template<class T>
    inline T mod(T x, T y) {
        while (x >= y)
            x -= y;
        while (x < 0)
            x += y;
        return x;
    }

    inline int_t floor_f(float_t x) {
        return x >= 0 ? (int_t) x : ((int_t) x) - 1;
    }

    inline long_t floor_d(double_t x) {
        return x >= 0 ? (long_t) x : ((long_t) x) - 1;
    }
}

#endif /* defined(__Serveur__MathUtils__) */
