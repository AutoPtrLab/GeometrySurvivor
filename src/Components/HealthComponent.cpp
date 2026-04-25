#include "Components/HealthComponent.h"
#include "Entity.h"
#include "Components/SimpleSpriteComponent.h"
HealthComponent::HealthComponent(int hp,float inviTime):health(hp),timer(inviTime){
    timer.setReady();
}

void HealthComponent::update(float dt){
    timer.update(dt);
    if(timer.checkTime(0.10f)){this->entity->getComponent<SimpleSpriteComponent>()->setHitColor();}
    else if(!timer.isReady()){
        this->entity->getComponent<SimpleSpriteComponent>()->setSecColor();
    }else{
        this->entity->getComponent<SimpleSpriteComponent>()->setFirstColor();
    }

}

void HealthComponent::getHit(int damage){
   // printf("%d\n",health);
    if(timer.isReady()){
        
        health-=damage;
        timer.reset();
        if(health <= 0){
            this->entity->destroy();
        }
    }
}