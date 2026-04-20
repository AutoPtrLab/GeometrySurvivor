#pragma once

#include "Component.h"
#include "Vector2D.h"
class TransformComponent;

class SimpleAIComponent: public Component<SimpleAIComponent>{

    private:
        float speed =0.0f;
        Vector2D dir;
        TransformComponent* tc=nullptr; 
        TransformComponent* target=nullptr;

    public:

        SimpleAIComponent(TransformComponent* target,float speed = 50.0f);
        void init() override;
        void update(float dt) override;

};