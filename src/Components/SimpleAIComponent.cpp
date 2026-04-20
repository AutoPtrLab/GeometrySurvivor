#include "Components/SimpleAIComponent.h"
#include "Components/TransformComponent.h"
#include "Entity.h"

SimpleAIComponent::SimpleAIComponent(TransformComponent* target,float speed):target(target),speed(speed){

}

void SimpleAIComponent::init(){
    tc=this->entity->getComponent<TransformComponent>();
}

void SimpleAIComponent::update(float dt){

    Vector2D playerPos = target->getPos();
    Vector2D thisPos = tc->getPos();
    Vector2D vectorEntityPlayer=(playerPos-thisPos);
    float dist=vectorEntityPlayer.getMagnitude();


    if(dist <= 3.0f){// if the distance is so small the component just stop(stops the jittering)
        tc->setVel(Vector2D{0,0});
    }else{
        dir=vectorEntityPlayer*(1/dist);
        tc->setVel(dir*speed);
    }
}
