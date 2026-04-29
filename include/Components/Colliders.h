#pragma once

#include "Components/ColliderComponent.h"

class SpellCollider : public ColliderComponent{
    public:

        SpellCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask );
        void onCollision(Entity* e) override;

};

class BulletCollider: public ColliderComponent{

    public:
        BulletCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask );
        void onCollision(Entity* e)override;
};

class EnemyCollider: public ColliderComponent{

    public:
        EnemyCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask );
        void onCollision(Entity* e) override;
};

class PlayerCollider:public ColliderComponent{

    public:
        PlayerCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask );
        void onCollision(Entity* e);
};