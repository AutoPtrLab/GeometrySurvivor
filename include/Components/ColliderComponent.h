#pragma once 
#include "Components/Component.h"
#include "Components/TransformComponent.h"

enum class ColliderFaction{ None,Enemy,Player,Bullet}; //tag to know which collisions must interact with each other

class TransformComponent;
class Vector2D;
class ColliderComponent:public Component<ColliderComponent>{

    private:

        float radius=0;
        ColliderFaction faction=ColliderFaction::None;
        TransformComponent* tc=nullptr;


    public:
        ColliderComponent(float radius,ColliderFaction fact);
        void init() override;
        void update(float dt) override;
        bool checkCollision(const ColliderComponent& other); //the entityManager will manage collisions
        Vector2D getPos() const{return tc->getPos();}
        float getRadius() const{return radius;}
        ColliderFaction getFaction() const{return faction;}
        
        
}; 