#include "ItemFood.h"

ItemFood::ItemFood(int_t healAmount, float_t saturationModifier, bool isWolfFavoriteMeat)
    : healAmount(healAmount), saturationModifier(saturationModifier), isWolfFavoriteMeat(isWolfFavoriteMeat) {}

ItemStack* ItemFood::onItemRightClick(ItemStack* stackIn, World* worldIn, EntityPlayer* playerIn) {
    if(playerIn->canEat(alwaysEdible)) {
            //TODO player -> Set Item in Use
    }

    return stackIn;
}

ItemStack* ItemFood::onItemUseFinish(ItemStack* stackIn, World* worldIn, EntityPlayer* playerIn) {
    stackIn->setCount(stackIn->getCount() - 1);
    playerIn->getFoodStats().addStats(this, stackIn);
    // TODO play sound in world
    // TODO Trigger achievement
    return stackIn;
}

varint_t ItemFood::getHealAmount() {
    return healAmount;
}

float_t ItemFood::getSaturationModifier() {
    return saturationModifier;
}

ItemFood* ItemFood::setAlwaysEdible(bool value) {
    alwaysEdible = value;
    return this;
}
