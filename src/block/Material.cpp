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

void Material::registerMaterials() {
    materials.push_back(air = new Material());
    materials.push_back(grass = new Material());
    materials.push_back(ground = new Material());
    materials.push_back(wood = (new Material())->setBurning());
    materials.push_back(rock = (new Material())->setRequiresTool());
    materials.push_back(iron = (new Material())->setRequiresTool());
    materials.push_back(anvil = (new Material())->setRequiresTool()->setImmovableMobility());
    materials.push_back(water = (new Material())->setNoPushMobility());
    materials.push_back(lava = (new Material())->setNoPushMobility());
    materials.push_back(leaves = (new Material())->setBurning()->setTranslucent()->setNoPushMobility());
    materials.push_back(plants = (new Material())->setNoPushMobility());
    materials.push_back(vine = (new Material())->setBurning()->setNoPushMobility()->setReplaceable());
    materials.push_back(sponge = new Material());
    materials.push_back(cloth = (new Material())->setBurning());
    materials.push_back(fire = (new Material())->setNoPushMobility());
    materials.push_back(sand = new Material());
    materials.push_back(circuits = (new Material())->setNoPushMobility());
    materials.push_back(carpet = (new Material())->setBurning());
    materials.push_back(glass = (new Material())->setTranslucent());
    materials.push_back(redstoneLight = new Material());
    materials.push_back(tnt = (new Material())->setBurning()->setTranslucent());
    materials.push_back(coral = (new Material())->setNoPushMobility());
    materials.push_back(ice = (new Material())->setTranslucent());
    materials.push_back(packedIce = new Material());
    materials.push_back(snow = (new Material())->setReplaceable()->setTranslucent()->setRequiresTool()->setNoPushMobility());
    materials.push_back(craftedSnow = (new Material())->setRequiresTool());
    materials.push_back(cactus = (new Material())->setTranslucent()->setNoPushMobility());
    materials.push_back(clay = new Material());
    materials.push_back(gourd = (new Material())->setNoPushMobility());
    materials.push_back(dragonEgg = (new Material())->setNoPushMobility());
    materials.push_back(portal = (new Material())->setImmovableMobility());
    materials.push_back(cake = (new Material())->setNoPushMobility());
    materials.push_back(web = new Material());
    materials.push_back(piston = (new Material())->setImmovableMobility());
    materials.push_back(barrier = (new Material())->setRequiresTool()->setImmovableMobility());
}

void Material::deregisterMaterials() {
    for (Material *material : materials)
        delete material;
}

Material::Material() {}

Material* Material::setBurning() {
    burning = true;
    return this;
}

Material* Material::setReplaceable() {
    replaceable = true;
    return this;
}

Material* Material::setTranslucent() {
    translucent = true;
    return this;
}

Material* Material::setRequiresTool() {
    requiresNoTool = false;
    return this;
}

Material* Material::setNoPushMobility() {
    mobility = 1;
    return this;
}

Material* Material::setImmovableMobility() {
    mobility = 2;
    return this;
}

std::vector<Material*> Material::materials;
