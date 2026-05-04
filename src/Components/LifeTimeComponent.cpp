#include "Components/LifeTimeComponent.h"
#include "Entity.h"
#include "Components/TransformComponent.h"


LifeTimeComponent::LifeTimeComponent(float lifeTime,std::function<void(Vector2D pos)> deathCallback):t(lifeTime),deathCallback(deathCallback){}

void LifeTimeComponent::update(float dt){
    t.update(dt);
    if(t.isReady()){
        if(deathCallback){
            deathCallback(this->entity->getComponent<TransformComponent>()->getPos());
        }
        this->entity->destroy();
    }

}