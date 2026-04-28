#include "Components/PlayerComponent.h"
#include "Components/HealthComponent.h"
#include "Entity.h"

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
void PlayerComponent::update(float dt){

}

void PlayerComponent::render(SDL::RendererPtr r){
    
    int hp = this->entity->getComponent<HealthComponent>()->getHealth(); //we dont check here becasue player has always hp
    
    float proportion = (hp/100.0f);
    SDL::setRenderDrawColor(r,255,0,0,150);
    SDL::Rect rect { 0,265,static_cast<int>(480*proportion),5};
    SDL::renderFillRect(r,rect);
}
