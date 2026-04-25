#pragma once 
#include "Components/Component.h"
#include "Components/TransformComponent.h"



class TransformComponent;
class Vector2D;
class ColliderComponent:public Component<ColliderComponent>{

    private:

        float radius=0;
        Faction faction=Faction::None;
        TransformComponent* tc=nullptr;


    public:
        ColliderComponent(float radius,Faction fact);
        void init() override;
        void update(float dt) override;
        bool checkCollision(const ColliderComponent& other); //the entityManager will manage collisions
        Vector2D getPos() const{return tc->getPos();}
        float getRadius() const{return radius;}
        Faction getFaction() const{return faction;}
        
        
}; 