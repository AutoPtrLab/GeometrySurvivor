#include "Components/TransformComponent.h"
 


TransformComponent::TransformComponent(Vector2D initpos):pos(initpos){
    vel=Vector2D{10,10};
}

void TransformComponent::update(float dt){
    
    vel+=accel*dt;
    pos+=vel*dt;

}