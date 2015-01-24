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

    AxisAlignedBB &add(double_t, double_t, double_t);

    double_t calculateXOffset(AxisAlignedBB, double_t);

    double_t calculateYOffset(AxisAlignedBB, double_t);

    double_t calculateZOffset(AxisAlignedBB, double_t);

    AxisAlignedBB &contract(double_t, double_t, double_t);

    AxisAlignedBB &expand(double_t, double_t, double_t);

    bool intersects(AxisAlignedBB);

    AxisAlignedBB &offset(double_t, double_t, double_t);

    AxisAlignedBB clone();
};

#endif /* defined(__Serveur__AxisAlignedBB__) */
