#pragma once 
#include "Components/Component.h"
#include "Components/TransformComponent.h"

namespace CollisionLayer{
    enum Type : uint16_t{//bit mask to resolve collisions

    None = 0,
    Player=1<<0,
    Enemy = 1<<1,
    Spell= 1<<2


};
};

class TransformComponent;
class Vector2D;
class ColliderComponent:public Component<ColliderComponent>{

    protected:

        float radius=0;
        CollisionLayer::Type layer=CollisionLayer::None; //where the object is
        CollisionLayer::Type  mask=CollisionLayer::None; // who does the object interact with
        TransformComponent* tc=nullptr;




    public:
        ColliderComponent(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask );
        void init() override;
        void update(float dt) override;
        bool checkCollision(const ColliderComponent& other); //the entityManager will manage collisions
        virtual void onCollision(Entity* e)=0;
        Vector2D getPos() const{return tc->getPos();}
        float getRadius() const{return radius;}
        CollisionLayer::Type getLayer() const{return layer;}
        CollisionLayer::Type getMask() const{return mask;}
        
        
}; 