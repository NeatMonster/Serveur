#ifndef __Serveur__AxisAlignedBB__
#define __Serveur__AxisAlignedBB__

#include "Types.h"

struct AxisAlignedBB {
    double_t minX;
    double_t minY;
    double_t minZ;
    double_t maxX;
    double_t maxY;
    double_t maxZ;

    void setDimension(double_t, double_t, double_t);

    void setPosition(double_t, double_t, double_t);
};

#endif /* defined(__Serveur__AxisAlignedBB__) */
