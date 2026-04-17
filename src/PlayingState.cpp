#include "PlayingState.h"
#include "Components/ComponentsList.h"

PlayingState::PlayingState(std::function <void(StateID)> chaState):State(chaState){

    auto &e=eManager.addEntity(3);
    e.addComponent<TransformComponent>(Vector2D{0,0}) ;

}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const SDL::Event &e){
    
    if (e.type == SDL_QUIT) {
        
        if(changeState) changeState(StateID::Close);
    }

}
void PlayingState::update(float dt){
    eManager.update(dt);
    eManager.garbageCollector();
}
void PlayingState::render(SDL::RendererPtr r){
    eManager.render();
}