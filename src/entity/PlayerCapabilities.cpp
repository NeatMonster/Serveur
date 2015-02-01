#include "PlayerCapabilities.h"

#include "NBTTagInt.h"

PlayerCapabilities::PlayerCapabilities() {}

void PlayerCapabilities::readCapabilitiesFromNBT(NBTTagCompound* tag) {
    std::shared_ptr<NBTTagCompound> abilities = tag->get("abilities")->asCompound();

    // TODO la suite
}

float_t PlayerCapabilities::getFlySpeed() {
    return flySpeed;
}

float_t PlayerCapabilities::getWalkSpeed() {
    return walkSpeed;
}
