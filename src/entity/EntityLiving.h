#ifndef __Serveur__EntityLiving__
#define __Serveur__EntityLiving__

#include "Entity.h"

class EntityLiving : public Entity {
public:
    EntityLiving(World*);

    virtual ~EntityLiving();

    virtual Type getType() = 0;

    void setHeadRotation(float_t);

    void jump();

    virtual void onTick();

protected:
    int_t headYaw, lastHeadYaw;
};

#endif /* defined(__Serveur__EntityLiving__) */
