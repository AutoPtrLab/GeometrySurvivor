#include "Components/LifeTimeComponent.h"
#include "Entity.h"


LifeTimeComponent::LifeTimeComponent(float lifeTime):t(lifeTime){}

void LifeTimeComponent::update(float dt){
    t.update(dt);
    if(t.isReady()){
        this->entity->destroy();
    }

}