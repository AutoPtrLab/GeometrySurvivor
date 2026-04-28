#pragma once

#include "Component.h"
#include "Timer.h"

class HealthComponent:public Component<HealthComponent>{

    private:
        Timer timer;//timer to have invincibilityFrames
        int health=0;

    public:
        HealthComponent(int hp,float inviTime=1.0f);
        int getHealth()const{return health;}
        void getHit(int damage);
        void update(float dt)override;
        
};