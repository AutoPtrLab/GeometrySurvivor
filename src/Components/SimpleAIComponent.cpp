#include "Components/SimpleAIComponent.h"
#include "Components/TransformComponent.h"
#include "Entity.h"
#include "RandomUtils.h"

SimpleAIComponent::SimpleAIComponent(infoAI& info):info(&info){
     
}

void SimpleAIComponent::init(){
    tc=this->entity->getComponent<TransformComponent>();
}

void SimpleAIComponent::update(float dt){
   

    if(!info->isPlayerAlive){  
        tc->setVel(Vector2D{0,0});
        return; //if player is dead we do nothing
    }
    
    Vector2D targetPos = info->playerPos;    
    Vector2D thisPos = tc->getPos();
    Vector2D vectorEntityPlayer=(targetPos-thisPos);
    float speed= tc->getSpeed();
    float dist=vectorEntityPlayer.getMagnitude(); //it cant be Sq

    
    if(dist <= 3.0f){// if the distance is so small the component just stop(stops the jittering)
        tc->setVel(Vector2D{0,0});
    }else{
        dir=vectorEntityPlayer*(1/dist);
        dir.x*=randomFloat(0.8f,1.2f);  //little bit of randomize to stop enemy pilling<<<<<<<
        dir.y*=randomFloat(0.8f,1.2f);
        tc->setVel(dir*speed);
    }
}
