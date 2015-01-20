#include "Material.h"

Material* Material::air;
Material* Material::grass;
Material* Material::ground;
Material* Material::wood;
Material* Material::rock;
Material* Material::iron;
Material* Material::anvil;
Material* Material::water;
Material* Material::lava;
Material* Material::leaves;
Material* Material::plants;
Material* Material::vine;
Material* Material::sponge;
Material* Material::cloth;
Material* Material::fire;
Material* Material::sand;
Material* Material::circuits;
Material* Material::carpet;
Material* Material::glass;
Material* Material::redstoneLight;
Material* Material::tnt;
Material* Material::coral;
Material* Material::ice;
Material* Material::packedIce;
Material* Material::snow;
Material* Material::craftedSnow;
Material* Material::cactus;
Material* Material::clay;
Material* Material::gourd;
Material* Material::dragonEgg;
Material* Material::portal;
Material* Material::cake;
Material* Material::web;
Material* Material::piston;
Material* Material::barrier;

std::vector<Material*> Material::materialList;

void Material::registerMaterials() {
    materialList.push_back(air = new Material());
    materialList.push_back(grass = new Material());
    materialList.push_back(ground = new Material());
    materialList.push_back(wood = (new Material())->setBurning());
    materialList.push_back(rock = (new Material())->setRequiresTool());
    materialList.push_back(iron = (new Material())->setRequiresTool());
    materialList.push_back(anvil = (new Material())->setRequiresTool()->setImmovableMobility());
    materialList.push_back(water = (new Material())->setNoPushMobility());
    materialList.push_back(lava = (new Material())->setNoPushMobility());
    materialList.push_back(leaves = (new Material())->setBurning()->setTranslucent()->setNoPushMobility());
    materialList.push_back(plants = (new Material())->setNoPushMobility());
    materialList.push_back(vine = (new Material())->setBurning()->setNoPushMobility()->setReplaceable());
    materialList.push_back(sponge = new Material());
    materialList.push_back(cloth = (new Material())->setBurning());
    materialList.push_back(fire = (new Material())->setNoPushMobility());
    materialList.push_back(sand = new Material());
    materialList.push_back(circuits = (new Material())->setNoPushMobility());
    materialList.push_back(carpet = (new Material())->setBurning());
    materialList.push_back(glass = (new Material())->setTranslucent()->setAdventureModeExempt());
    materialList.push_back(redstoneLight = (new Material())->setAdventureModeExempt());
    materialList.push_back(tnt = (new Material())->setBurning()->setTranslucent());
    materialList.push_back(coral = (new Material())->setNoPushMobility());
    materialList.push_back(ice = (new Material())->setTranslucent()->setAdventureModeExempt());
    materialList.push_back(packedIce = (new Material())->setAdventureModeExempt());
    materialList.push_back(snow = (new Material())->setReplaceable()->setTranslucent()->setRequiresTool()->setNoPushMobility());
    materialList.push_back(craftedSnow = (new Material())->setRequiresTool());
    materialList.push_back(cactus = (new Material())->setTranslucent()->setNoPushMobility());
    materialList.push_back(clay = new Material());
    materialList.push_back(gourd = (new Material())->setNoPushMobility());
    materialList.push_back(dragonEgg = (new Material())->setNoPushMobility());
    materialList.push_back(portal = (new Material())->setImmovableMobility());
    materialList.push_back(cake = (new Material())->setNoPushMobility());
    materialList.push_back(web = new Material());
    materialList.push_back(piston = (new Material())->setImmovableMobility());
    materialList.push_back(barrier = (new Material())->setRequiresTool()->setImmovableMobility());
}

void Material::deregisterMaterials() {
    for (Material* material : materialList)
        delete material;
}

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
