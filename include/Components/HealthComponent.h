#pragma once

#include "Component.h"
#include "Timer.h"

struct StatusEffect{
        
    float speedMult={1.0f};
    float damageTick={1.0f};
    int damage=0;
    SDL::Color statusColor={255,255,255,255};

};

namespace Status {
    inline constexpr StatusEffect None  = {1.0f,  0.0f, 0,  {255,255,255,255}};
    inline constexpr StatusEffect Frozen  = {0.5f,  0.0f, 0,  SDL::Colors::Ice};
    inline constexpr StatusEffect Burn  = {1.2f,  0.3f, 2, SDL::Colors::Pumpkin};
    inline constexpr StatusEffect Stun  = {0.0f,  0.0f, 0,  SDL::Colors::Electric};
    
}


 
class HealthComponent:public Component<HealthComponent>{
    
    

    private:
        Timer timer;//timer to have invincibilityFrames
        Timer statusTimer{0.0f};//how much the status is going to last
        Timer statusDamageTimer{0.0f};

        int health=0;
        const StatusEffect* status = &Status::None ;

    public:
        HealthComponent(int hp,float inviTime=1.0f);
        int getHealth()const{return health;}
        void getHit(int damage);
        void update(float dt)override;
        void setStatus(const StatusEffect *st ,float dur);
        const StatusEffect* getStatus()const{return status;}
        
};