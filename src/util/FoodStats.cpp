#include "FoodStats.h"

#include "EntityPlayer.h"
#include "ItemFood.h"
#include "Level.h"
#include "MathUtils.h"
#include "NBTTagInt.h"
#include "NBTTagFloat.h"

FoodStats::FoodStats() : foodLevel(20), saturationLevel(5.0F)
{}

void FoodStats::addStats(varint_t foodAmount, float_t saturationAmount) {
    foodLevel = MathUtils::min(foodLevel + foodAmount, varint_t(20));
    saturationAmount = MathUtils::min(saturationLevel + saturationAmount * foodAmount * 2.0F, (float_t)foodLevel);
}

void FoodStats::addStats(ItemFood* itemFood, ItemStack* stack) {
    addStats(itemFood->getHealAmount(), itemFood->getSaturationModifier());
}

void FoodStats::onUpdate(EntityPlayer* player) {
    Level::Difficulty difficulty = player->getWorld()->getLevel()->getDifficulty();

    if (exhaustionLevel > 4.0F)
    {
        exhaustionLevel -= 4.0F;
        if(saturationLevel > 0.0F)
            saturationLevel = MathUtils::max(saturationLevel - 1.0F, 0.0F);
        if(difficulty != Level::Difficulty::PEACEFUL)
            foodLevel = MathUtils::max(foodLevel - 1, varint_t(0));
    }

    if(player->getWorld()->getLevel()->getGameRules().getGameRuleBooleanValue("naturalRegeneration") && foodLevel >= 18 && player->shouldHeal()) {
        ++foodTimer;

        if(foodTimer >= 80) {
            player->heal(1.0F);
            addExhaustion(3.0F);
            foodTimer = 0;
        }
    }
    else if(foodLevel <= 0) {
        ++foodTimer;

        if(foodTimer >= 80) {
            if(player->getHealth() > 10.0F || difficulty == Level::Difficulty::HARD || player->getHealth() > 1.0F && difficulty == Level::Difficulty::NORMAL) {
                //player->attackEntity(1.0F); TODO
            }

            foodTimer = 0;
        }
    }
    else
        foodTimer = 0;
}

void FoodStats::readNBT(NBTTagCompound& tag) {
    foodTimer = tag.get("foodTimer")->asInt()->get();
    foodLevel = tag.get("foodLevel")->asInt()->get();
    saturationLevel = tag.get("foodSaturationLevel")->asFloat()->get();
    exhaustionLevel = tag.get("foodExhaustionLevel")->asFloat()->get();
}

void FoodStats::setFoodLevel(varint_t level) {
    foodLevel = level;
}

varint_t FoodStats::getFoodLevel() {
    return foodLevel;
}

bool FoodStats::needFood() {
    return foodLevel < 20;
}

float_t FoodStats::getSaturationLevel() {
    return saturationLevel;
}

void FoodStats::addExhaustion(float_t amount) {
    exhaustionLevel = MathUtils::min(exhaustionLevel + amount, 40.0F);
}
