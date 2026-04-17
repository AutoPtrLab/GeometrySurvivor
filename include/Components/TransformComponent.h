#pragma once
#include "Component.h"
#include "Vector2D.h"
class TransformComponent: public Component<TransformComponent>{

    private:

        Vector2D pos;//position vector
        Vector2D vel;//velocity
        Vector2D accel; //acceleration         

    public:

        TransformComponent(Vector2D initPos);
        void update(float dt) override;


} ;