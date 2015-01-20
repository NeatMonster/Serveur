#ifndef __Serveur__Material__
#define __Serveur__Material__

#include <vector>

class Material {
public:
    static Material* air;
    static Material* grass;
    static Material* ground;
    static Material* wood;
    static Material* rock;
    static Material* iron;
    static Material* anvil;
    static Material* water;
    static Material* lava;
    static Material* leaves;
    static Material* plants;
    static Material* vine;
    static Material* sponge;
    static Material* cloth;
    static Material* fire;
    static Material* sand;
    static Material* circuits;
    static Material* carpet;
    static Material* glass;
    static Material* redstoneLight;
    static Material* tnt;
    static Material* coral;
    static Material* ice;
    static Material* packedIce;
    static Material* snow;
    static Material* craftedSnow;
    static Material* cactus;
    static Material* clay;
    static Material* gourd;
    static Material* dragonEgg;
    static Material* portal;
    static Material* cake;
    static Material* web;
    static Material* piston;
    static Material* barrier;

    static void registerMaterials();

    static void deregisterMaterials();

    Material(); //TODO Ajouter la MapColor (pas prioritaire)

private:
    bool canBurn;
    bool replaceable;
    bool isTranslucent;
    bool requiresNoTool = true;
    bool isAdventureModeExempt;
    int mobilityFlag;

    static std::vector<Material*> materialList;

protected:
    Material* setBurning();
    Material* setReplaceable();
    Material* setTranslucent();
    Material* setRequiresTool();
    Material* setNoPushMobility();
    Material* setImmovableMobility();
    Material* setAdventureModeExempt();

public:
    bool getCanBurn();
    bool isReplaceable();
    bool isOpaque();
    bool blocksMovement();
    bool blocksLight();
    int getMaterialMobility();
};

#endif // __Serveur__Material__
