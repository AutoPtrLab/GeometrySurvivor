#include "Components/ColliderComponent.h"
#include "Components/TransformComponent.h"
#include "Entity.h"
#include "Vector2D.h"
ColliderComponent::ColliderComponent(float radius, CollisionLayer::Type layer,CollisionLayer::Type mask ):radius(radius),layer(layer),mask(mask){}


void ColliderComponent::init(){
    tc=this->entity->getComponent<TransformComponent>();
}

void ColliderComponent::update(float dt){

}


bool ColliderComponent::checkCollision(const ColliderComponent &other){
    
    return Vector2D(getPos() - other.getPos()).getMagnitudeSq()< ((radius + other.getRadius())*(radius + other.getRadius())); //the distance are squared so we can avoid sqrtroots
 }
     

