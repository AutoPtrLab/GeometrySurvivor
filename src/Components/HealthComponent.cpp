#include "Components/HealthComponent.h"
#include "Entity.h"
#include "Components/SimpleSpriteComponent.h"
#include "Components/TransformComponent.h"
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


    if(status != &Status::None){
        
        statusDamageTimer.update(dt);
        statusTimer.update(dt);

        if(statusDamageTimer.isReady()){
            if(status->damage>0){
                getHit(status->damage);
                statusDamageTimer.reset();
            }
        }
        if(statusTimer.isReady()){
            
            this->entity->getComponent<TransformComponent>()->setSpeedMult(1.0f);//we go back to normal
            statusTimer.reset();
            status=&Status::None;
        }
    }

}


void HealthComponent::setStatus(const StatusEffect* st ,float dur){
   
    if(st == status ){
        statusTimer.startTimer(dur);

    }else{
        this->entity->getComponent<TransformComponent>()->MultMultiplicator(1/status->speedMult);//we go back to normal
        status=(st);
        this->entity->getComponent<TransformComponent>()->MultMultiplicator(status->speedMult);
        //add enityt to represetn the status
        statusDamageTimer.startTimer(st->damageTick);
        statusTimer.startTimer(dur);
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