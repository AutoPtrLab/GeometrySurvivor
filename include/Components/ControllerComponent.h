#pragma once
#include "Component.h"
#include "Vector2D.h"

class TransformComponent; 
class ControllerComponent : public Component<ControllerComponent>{

    private:


        float speed=0; //
        Vector2D dir;//vector betweeen the character and the mouse cursor

        TransformComponent *tc=nullptr;

    public:
        
        ControllerComponent(float speed);
        void init() override;
        void update(float dt) override;

        void setSpeed(float newSpe){speed=newSpe;}

};