#include "Components/SimpleAIComponent.h"
#include "Components/TransformComponent.h"
#include "Entity.h"

SimpleAIComponent::SimpleAIComponent(infoAI& info,float speed):info(&info),speed(speed){
     
}

void SimpleAIComponent::init(){
    tc=this->entity->getComponent<TransformComponent>();
}

void SimpleAIComponent::update(float dt){
   

    if(!info->isPlayerAlive){  
        tc->setVel(Vector2D{0,0});
        return; //if player is dead we do nothing
    }
    
    Vector2D playerPos = info->playerPos;    
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
