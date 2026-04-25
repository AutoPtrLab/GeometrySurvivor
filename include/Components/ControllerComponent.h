#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "vector"

class TransformComponent; 
class ControllerComponent : public Component<ControllerComponent>{

    private:


        float speed=0; //
        Vector2D dir;//vector betweeen the character and the mouse cursor

        std::vector<SDL_Event>& keyPressedVec;

        TransformComponent *tc=nullptr;

    public:
        
        ControllerComponent(float speed,std::vector<SDL_Event>& keyPressedVec);
        void init() override;
        void update(float dt) override;
        

        void setSpeed(float newSpe){speed=newSpe;}

};