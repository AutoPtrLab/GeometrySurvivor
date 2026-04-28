#pragma once

#include "Components/ColliderComponent.h"

class SpellColliderComponent : public ColliderComponent{

    void onCollision(Entity& e) override;

};

class BulletColliderComponent: public ColliderComponent{
    void onCollision(Entity& e)override;
};