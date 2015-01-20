#ifndef __Serveur__Material__
#define __Serveur__Material__


class Material {
public:
    static const Material* air;
    static const Material* grass;
    static const Material* ground;
    static const Material* wood;
    static const Material* rock;
    static const Material* iron;
    static const Material* anvil;
    static const Material* water;
    static const Material* lava;
    static const Material* leaves;
    static const Material* plants;
    static const Material* vine;
    static const Material* sponge;
    static const Material* cloth;
    static const Material* fire;
    static const Material* sand;
    static const Material* circuits;
    static const Material* carpet;
    static const Material* glass;
    static const Material* redstoneLight;
    static const Material* tnt;
    static const Material* coral;
    static const Material* ice;
    static const Material* packedIce;
    static const Material* snow;
    static const Material* craftedSnow;
    static const Material* cactus;
    static const Material* clay;
    static const Material* gourd;
    static const Material* dragonEgg;
    static const Material* portal;
    static const Material* cake;
    static const Material* web;
    static const Material* piston;
    static const Material* barrier;

    Material(); //TODO Ajouter la MapColor (pas prioritaire)

private:
    bool canBurn;
    bool replaceable;
    bool isTranslucent;
    bool requiresNoTool = true;
    bool isAdventureModeExempt;
    int mobilityFlag;

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
