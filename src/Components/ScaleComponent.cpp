#include "Components/ScaleComponent.h"
#include "Entity.h"
#include "Components/SimpleSpriteComponent.h"
#include "Components/ColliderComponent.h"
#include <cmath>

float lerp(float current,float target, float t){
    return current+(target-current)*t;
}

ScaleComponent::ScaleComponent(){
}

ScaleComponent::ScaleComponent(float targetS,float scaleS):targetScale(targetS),scaleSpeed(scaleS){

}


void ScaleComponent::init(){

    cc=this->entity->getComponent<ColliderComponent>();
    ssc=this->entity->getComponent<SimpleSpriteComponent>();
    origRad=ssc->getRadius();

}

void ScaleComponent::update(float dt){

    if(scale == targetScale) return; //if is the same scale we dont do anything

    scale = lerp(scale,targetScale,dt*scaleSpeed);

    if(std::abs(scale-targetScale)<0.01f){
        scale=targetScale;
    }

    cc->setRadius(scale*origRad);
    ssc->setRadius(scale*origRad);
    
    
    
}


