#include "Components/TransformComponent.h"
 


TransformComponent::TransformComponent(Vector2D initpos):pos(initpos){}

void TransformComponent::update(float dt){
    
    vel+=accel*dt;
    pos+=vel*dt;

}