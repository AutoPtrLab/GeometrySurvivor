#include "Components/PlayerComponent.h"


PlayerComponent::PlayerComponent(std::function<void(Entity& player)> setPlayerFunc,std::function<void()> destPlayerFunc)
:setPlayer(setPlayerFunc),destroyPlayer(destPlayerFunc){
   
}

void PlayerComponent::init(){
     if(setPlayer){
        setPlayer(*this->entity);
    } //we make this entity the Player
}

PlayerComponent:: ~PlayerComponent(){
    if(destroyPlayer) destroyPlayer();
}

