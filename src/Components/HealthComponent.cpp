#include "Components/HealthComponent.h"
#include "Entity.h"
HealthComponent::HealthComponent(int hp,float inviTime):health(hp),timer(inviTime){}

void HealthComponent::update(float dt){
    timer.update(dt);

}

void HealthComponent::getHit(int damage){

    if(timer.isReady()){
        health-=damage;
        timer.reset();
        if(health <= 0){
            this->entity->destroy();
        }
    }
}