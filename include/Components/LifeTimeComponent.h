#pragma once
#include "Component.h"
#include "Timer.h"
#include <functional> 
#include "Vector2D.h"
class LifeTimeComponent : public Component<LifeTimeComponent>{

    private:

        std::function<void(Vector2D pos)> deathCallback; 
        Timer t;//lifetime of the entity

    public:

        LifeTimeComponent(float lifeTime,std::function<void(Vector2D pos)> deathCallback=nullptr); 
        void update(float dt);

} ; 