#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "infoAI.h"

 
class TransformComponent;

class SimpleAIComponent: public Component<SimpleAIComponent>{

    protected:
       
        Vector2D dir;
        TransformComponent* tc=nullptr; 
        //Faction targetFaction=Faction::None; //mode to aim towards the player or the nearest enemy
        
        infoAI *info=nullptr;

    public:

        SimpleAIComponent(infoAI &info);
        void init() override;
        virtual void update(float dt) override;

};