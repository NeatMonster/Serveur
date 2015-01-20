#include "Material.h"

const Material* Material::air = new Material();
const Material* Material::grass = new Material();
const Material* Material::ground = new Material();
const Material* Material::wood = (new Material())->setBurning();
const Material* Material::rock = (new Material())->setRequiresTool();
const Material* Material::iron = (new Material())->setRequiresTool();
const Material* Material::anvil = (new Material())->setRequiresTool()->setImmovableMobility();
const Material* Material::water = (new Material())->setNoPushMobility();
const Material* Material::lava = (new Material())->setNoPushMobility();
const Material* Material::leaves = (new Material())->setBurning()->setTranslucent()->setNoPushMobility();
const Material* Material::plants = (new Material())->setNoPushMobility();
const Material* Material::vine = (new Material())->setBurning()->setNoPushMobility()->setReplaceable();
const Material* Material::sponge = new Material();
const Material* Material::cloth = (new Material())->setBurning();
const Material* Material::fire = (new Material())->setNoPushMobility();
const Material* Material::sand = new Material();
const Material* Material::circuits = (new Material())->setNoPushMobility();
const Material* Material::carpet = (new Material())->setBurning();
const Material* Material::glass = (new Material())->setTranslucent()->setAdventureModeExempt();
const Material* Material::redstoneLight = (new Material())->setAdventureModeExempt();
const Material* Material::tnt = (new Material())->setBurning()->setTranslucent();
const Material* Material::coral = (new Material())->setNoPushMobility();
const Material* Material::ice = (new Material())->setTranslucent()->setAdventureModeExempt();
const Material* Material::packedIce = (new Material())->setAdventureModeExempt();
const Material* Material::snow = (new Material())->setReplaceable()->setTranslucent()->setRequiresTool()->setNoPushMobility();
const Material* Material::craftedSnow = (new Material())->setRequiresTool();
const Material* Material::cactus = (new Material())->setTranslucent()->setNoPushMobility();
const Material* Material::clay = new Material();
const Material* Material::gourd = (new Material())->setNoPushMobility();
const Material* Material::dragonEgg = (new Material())->setNoPushMobility();
const Material* Material::portal = (new Material())->setImmovableMobility();
const Material* Material::cake = (new Material())->setNoPushMobility();
const Material* Material::web = new Material();
const Material* Material::piston = (new Material())->setImmovableMobility();
const Material* Material::barrier = (new Material())->setRequiresTool()->setImmovableMobility();

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
