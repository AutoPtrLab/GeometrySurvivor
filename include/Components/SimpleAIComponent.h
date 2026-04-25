#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "infoAI.h"

 
class TransformComponent;

class SimpleAIComponent: public Component<SimpleAIComponent>{

    private:
       
        Vector2D dir;
        TransformComponent* tc=nullptr; 
        Faction targetFaction=Faction::None; //mode to aim towards the player or the nearest enemy
        
        infoAI *info=nullptr;
        float speed =0.0f;


    public:

        SimpleAIComponent(infoAI &info,float speed = 50.0f);
        void init() override;
        void update(float dt) override;

};