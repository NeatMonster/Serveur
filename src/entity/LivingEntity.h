#ifndef __Serveur__LivingEntity__
#define __Serveur__LivingEntity__

#include "Entity.h"

class LivingEntity : public Entity {
public:
    LivingEntity(World*);

    virtual ~LivingEntity();

    virtual Type getType() = 0;

    virtual void setPosition(double_t, double_t, double_t);

    virtual void setRotation(float_t, float_t);

    virtual void setHeadRotation(float_t);

    virtual void onTick();

protected:
    int_t headYaw, lastHeadYaw;
};

#endif /* defined(__Serveur__LivingEntity__) */
