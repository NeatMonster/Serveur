#include "AxisAlignedBB.h"

void AxisAlignedBB::setDimension(double_t x, double_t y, double_t z) {
    maxX = minX + x;
    maxY = minY + y;
    maxZ = minZ + z;
}

void AxisAlignedBB::setPosition(double_t x, double_t y, double_t z) {
    maxX = x + (maxX - minX);
    minX = x;
    maxY = y + (maxY - minY);
    minY = y;
    maxZ = z + (maxZ - minZ);
    minZ = z;
}
