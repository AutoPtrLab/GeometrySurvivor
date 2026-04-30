#include "Components/TransformComponent.h"
 


TransformComponent::TransformComponent(Vector2D initpos,float s):pos(initpos),speed(s){
    
}

void TransformComponent::update(float dt){
    
    vel+=accel*dt;
    pos+=vel*dt*speedMult;

}