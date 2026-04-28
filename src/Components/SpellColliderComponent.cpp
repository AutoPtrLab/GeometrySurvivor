#include "SpellColliderComponent.h"
#include "Components/HealthComponent.h"
#include "Entity.h"



void SpellColliderComponent::onCollision(Entity& e){
    if(e.getComponent<HealthComponent>())
        e.getComponent<HealthComponent>()->getHit(20);
}



