#include "Components/Colliders.h"
#include "Components/HealthComponent.h"
#include "Entity.h"

SpellCollider::SpellCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask ):ColliderComponent(radius,layer,mask){}

void SpellCollider::onCollision(Entity* e){
    if(e->getComponent<HealthComponent>())
        e->getComponent<HealthComponent>()->getHit(20);
    

}

BulletCollider::BulletCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask ):ColliderComponent(radius,layer,mask){}
void BulletCollider::onCollision(Entity* e){
    if(e->getComponent<HealthComponent>())
        e->getComponent<HealthComponent>()->getHit(10);

    this->entity->destroy();
}

EnemyCollider::EnemyCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask ):ColliderComponent(radius,layer,mask){}
void EnemyCollider::onCollision(Entity* e){
    if(e->getComponent<HealthComponent>())
        e->getComponent<HealthComponent>()->getHit(10);
}

PlayerCollider::PlayerCollider(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask ):ColliderComponent(radius,layer,mask){}
void PlayerCollider::onCollision(Entity* e){
    
}
