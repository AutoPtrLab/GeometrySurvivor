#pragma once
#include "Component.h"
#include "Timer.h"
 
class LifeTimeComponent : public Component<LifeTimeComponent>{

    private:

        Timer t;//lifetime of the entity

    public:

        LifeTimeComponent(float lifeTime);
        void update(float dt);

} ; 