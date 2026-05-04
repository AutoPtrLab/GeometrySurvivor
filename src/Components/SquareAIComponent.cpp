#include "Components/SquareAIComponent.h"
#include "Components/TransformComponent.h"

SquareAIComponent::SquareAIComponent(infoAI& info,float dashDuration,float stopDuration,float dashCooldown):SimpleAIComponent(info),dashDuration(dashDuration),
stopDuration(stopDuration),dashCooldown(dashCooldown){}

void SquareAIComponent::update(float dt){

    if(!info->isPlayerAlive){
        tc->setVel(Vector2D{0,0});
        return;
    }

    float speed= tc->getSpeed();

    switch (state)
    {
    case State::Stop: 
        stopDuration.update(dt);
        tc->setVel(Vector2D{0,0});
        if(stopDuration.isReady()) {
            state=State::Dashing;
            stopDuration.reset();
            tc->setVel(dir*3.0f*speed);
        }
        
        break;
    case State::Dashing:
        dashDuration.update(dt);
        if(dashDuration.isReady()){
            state=State::Chasing;
            dashDuration.reset();
        }
        break;
    case State::Chasing:{

        Vector2D targetPos = info->playerPos;    
        Vector2D thisPos = tc->getPos();
        Vector2D vectorEntityPlayer=(targetPos-thisPos);
        float dist=vectorEntityPlayer.getMagnitude(); //it cant be Sq
        dir=vectorEntityPlayer*(1/dist);
        dashCooldown.update(dt); //we have another cooldawn so it can actually chase if is in the range
        if(dist <= 70.0f && dashCooldown.isReady()){// if the distance is near enough it tries to dash but cannot redirect mid dash
            
             //we save the direction before the dash
            state=State::Stop;
            dashCooldown.reset();
        }else{
            tc->setVel(dir*speed);
        }
        break;
    }
    default:
        break;
    }

}