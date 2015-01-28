#include "ItemBlock.h"

ItemBlock::ItemBlock(Block *block) : block(block) {}

Block *ItemBlock::getBlock() {
    return block;
}
