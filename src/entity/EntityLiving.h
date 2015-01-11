#ifndef __Serveur__EntityLiving__
#define __Serveur__EntityLiving__

#include "Entity.h"

class EntityLiving : public Entity {
public:
    EntityLiving(World*);

    virtual ~EntityLiving();

    virtual Type getType() = 0;

    virtual void move(double_t, double_t, double_t);

    virtual void rotate(float_t, float_t);

    void setHeadRotation(float_t);

    void rotateHead(float_t);

    void onTick();

protected:
    int_t headYaw, lastHeadYaw;
};

#endif /* defined(__Serveur__EntityLiving__) */
