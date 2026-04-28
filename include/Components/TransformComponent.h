#pragma once
#include "Component.h"
#include "Vector2D.h"
class TransformComponent: public Component<TransformComponent>{

    private:

        Vector2D pos;//position vector
        Vector2D vel;//velocity
        float speed=0.0f; //magnitude of velocity
        Vector2D accel; //acceleration         

    public:

        TransformComponent(Vector2D initPos,float s=0.0f);

        void update(float dt) override;


        Vector2D getPos()const{return pos;}
        void setPos(Vector2D newPos) {pos=newPos;}

        Vector2D getVel() const{return vel;}
        void setVel(Vector2D newVel){vel=newVel;}
        void MultVel(float mult){vel*=mult;}

        void setSpeed(float s){speed=s;}
        float getSpeed()const {return speed;}

        Vector2D getAccel() const{return accel;}
        void setAccel(Vector2D newAccel){accel=newAccel;}

        
} ;