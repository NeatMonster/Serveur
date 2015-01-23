#include "BlockAir.h"

BlockAir::BlockAir() : Block(Material::air) {
    boundingBox = {0, 0, 0, 0, 0, 0};
}
