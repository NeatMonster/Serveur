#include "Material.h"

Material* Material::air = new Material();
Material* Material::grass = new Material();
Material* Material::ground = new Material();
Material* Material::wood = (new Material())->setBurning();
Material* Material::rock = (new Material())->setRequiresTool();
Material* Material::iron = (new Material())->setRequiresTool();
Material* Material::anvil = (new Material())->setRequiresTool()->setImmovableMobility();
Material* Material::water = (new Material())->setNoPushMobility();
Material* Material::lava = (new Material())->setNoPushMobility();
Material* Material::leaves = (new Material())->setBurning()->setTranslucent()->setNoPushMobility();
Material* Material::plants = (new Material())->setNoPushMobility();
Material* Material::vine = (new Material())->setBurning()->setNoPushMobility()->setReplaceable();
Material* Material::sponge = new Material();
Material* Material::cloth = (new Material())->setBurning();
Material* Material::fire = (new Material())->setNoPushMobility();
Material* Material::sand = new Material();
Material* Material::circuits = (new Material())->setNoPushMobility();
Material* Material::carpet = (new Material())->setBurning();
Material* Material::glass = (new Material())->setTranslucent()->setAdventureModeExempt();
Material* Material::redstoneLight = (new Material())->setAdventureModeExempt();
Material* Material::tnt = (new Material())->setBurning()->setTranslucent();
Material* Material::coral = (new Material())->setNoPushMobility();
Material* Material::ice = (new Material())->setTranslucent()->setAdventureModeExempt();
Material* Material::packedIce = (new Material())->setAdventureModeExempt();
Material* Material::snow = (new Material())->setReplaceable()->setTranslucent()->setRequiresTool()->setNoPushMobility();
Material* Material::craftedSnow = (new Material())->setRequiresTool();
Material* Material::cactus = (new Material())->setTranslucent()->setNoPushMobility();
Material* Material::clay = new Material();
Material* Material::gourd = (new Material())->setNoPushMobility();
Material* Material::dragonEgg = (new Material())->setNoPushMobility();
Material* Material::portal = (new Material())->setImmovableMobility();
Material* Material::cake = (new Material())->setNoPushMobility();
Material* Material::web = new Material();
Material* Material::piston = (new Material())->setImmovableMobility();
Material* Material::barrier = (new Material())->setRequiresTool()->setImmovableMobility();

Material::Material() {
    //Implémenter le mapcolor par la suite
}

Material* Material::setBurning() {
    canBurn = true;
    return this;
}

Material* Material::setReplaceable() {
    replaceable = true;
    return this;
}

Material* Material::setTranslucent() {
    isTranslucent = true;
    return this;
}

Material* Material::setRequiresTool() {
    requiresNoTool = false;
    return this;
}

Material* Material::setNoPushMobility() {
    mobilityFlag = 1;
    return this;
}

Material* Material::setImmovableMobility() {
    mobilityFlag = 2;
    return this;
}

Material* Material::setAdventureModeExempt() {
    isAdventureModeExempt = true;
    return this;
}

bool Material::blocksLight() {
    return true;
}

bool Material::blocksMovement() {
    return true;
}

bool Material::isReplaceable() {
    return replaceable;
}

bool Material::isOpaque() {
    return isTranslucent ? false : blocksMovement();
}

bool Material::getCanBurn() {
    return canBurn;
}

int Material::getMaterialMobility() {
    return mobilityFlag;
}
