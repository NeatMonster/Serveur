#ifndef __Serveur__LivingEntity__
#define __Serveur__LivingEntity__

#include "Entity.h"

class LivingEntity : public Entity {
public:
    LivingEntity(World*);

    virtual ~LivingEntity();

    virtual void getType() = 0;

    void rotateHead(float_t);

    virtual void onTick();

protected:
    int_t headYaw, lastHeadYaw;
};

#endif /* defined(__Serveur__LivingEntity__) */
