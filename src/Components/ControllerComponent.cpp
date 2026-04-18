#include "Components/ControllerComponent.h"
#include "Entity.h"
#include "Components/TransformComponent.h"

ControllerComponent:: ControllerComponent(float speed):speed(speed){}
void ControllerComponent::init(){
    tc = this->entity->getComponent<TransformComponent>();
}
void ControllerComponent::update(float dt){

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    float logicalX = mouseX * (static_cast<float>(WIDTH) / WIN_WIDTH);
    float logicalY = mouseY * (static_cast<float>(HEIGHT) / WIN_HEIGHT);

    Vector2D mousePos={logicalX,logicalY};
    Vector2D playerPos = tc->getPos();
    Vector2D vectorPlayerMouse=(mousePos-playerPos);
    float dist=vectorPlayerMouse.getMagnitude();


    if(dist <= 1.0f){// if the distance is so small the component just stop(stops the jittering)
        tc->setVel(Vector2D{0,0});
    }else{
        dir=vectorPlayerMouse*(1/dist);
        tc->setVel(dir*speed);
    }

}