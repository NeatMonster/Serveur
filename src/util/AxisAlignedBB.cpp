#include "AxisAlignedBB.h"

AxisAlignedBB &AxisAlignedBB::add(double_t x, double_t y, double_t z) {
    if (x > 0)
        maxX += x;
    else
        minX += x;
    if (y > 0)
        maxY += y;
    else
        minY += y;
    if (z > 0)
        maxZ += z;
    else
        minZ += z;
    return *this;
}

double_t AxisAlignedBB::calculateXOffset(AxisAlignedBB other, double_t offset) {
    if (minY < other.maxY && maxY > other.minY && minZ < other.maxZ && maxZ > other.minZ) {
        if (offset > 0 && minX >= other.maxX) {
            double_t delta = minX - other.maxX;
            if (delta < offset)
                offset = delta;
        } else if (offset < 0 && maxX <= other.minX) {
            double_t delta = maxX - other.minX;
            if (delta > offset)
                offset = delta;
        }
    }
    return offset;
}

double_t AxisAlignedBB::calculateYOffset(AxisAlignedBB other, double_t offset) {
    if (minX < other.maxX && maxX > other.minX && minZ < other.maxZ && maxZ > other.minZ) {
        if (offset > 0 && minY >= other.maxY) {
            double_t delta = minY - other.maxY;
            if (delta < offset)
                offset = delta;
        } else if (offset < 0 && maxY <= other.minY) {
            double_t delta = maxY - other.minY;
            if (delta > offset)
                offset = delta;
        }
    }
    return offset;
}

double_t AxisAlignedBB::calculateZOffset(AxisAlignedBB other, double_t offset) {
    if (minX < other.maxX && maxX > other.minX && minY < other.maxY && maxY > other.minY) {
        if (offset > 0 && minZ >= other.maxZ) {
            double_t delta = minZ - other.maxZ;
            if (delta < offset)
                offset = delta;
        } else if (offset < 0 && maxZ <= other.minZ) {
            double_t delta = maxZ - other.minZ;
            if (delta > offset)
                offset = delta;
        }
    }
    return offset;
}

AxisAlignedBB &AxisAlignedBB::contract(double_t x, double_t y, double_t z) {
    minX += x;
    maxX -= x;
    minY += y;
    maxY -= y;
    minZ += z;
    return *this;
}

AxisAlignedBB &AxisAlignedBB::expand(double_t x, double_t y, double_t z) {
    minX -= x;
    maxX += x;
    minY -= y;
    maxY += y;
    minZ -= z;
    maxZ += z;
    return *this;
}

bool AxisAlignedBB::intersects(AxisAlignedBB other) {
    return maxX > other.minX && minX < other.maxX && maxY > other.minY
        && minY < other.maxX && maxZ > other.minZ && minZ < other.maxZ;
}

AxisAlignedBB &AxisAlignedBB::offset(double_t x, double_t y, double_t z) {
    minX += x;
    maxX += x;
    minY += y;
    maxY += y;
    minZ += z;
    maxZ += z;
    return *this;
}

AxisAlignedBB AxisAlignedBB::clone() {
    return {minX, minY, minZ, maxX, maxY, maxZ};
}
