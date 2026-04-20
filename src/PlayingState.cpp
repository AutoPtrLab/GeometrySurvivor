#include "PlayingState.h"
#include "Components/ComponentsList.h"

PlayingState::PlayingState(std::function <void(StateID)> chaState):State(chaState),cManager(eManager.getUpdateVec()){

    auto &e=eManager.addEntity(1);
    e.addComponent<TransformComponent>(Vector2D{400,20}) ;
    e.addComponent<SimpleSpriteComponent>();
    e.addComponent<ControllerComponent>(70.0f);
    e.addComponent<ColliderComponent>(4.0f,Faction::Player);
    e.addComponent<HealthComponent>(100);
    e.init();

    auto &e2=eManager.addEntity(2);
    e2.addComponent<TransformComponent>(Vector2D{50,50}) ;
    e2.addComponent<SimpleSpriteComponent>();
    e2.addComponent<SimpleAIComponent>(e.getComponent<TransformComponent>(),30.0f);
    e2.addComponent<ColliderComponent>(4.0f,Faction::Enemy);
    e2.init(); 

}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const SDL::Event &e){
    
    if (e.type == SDL_QUIT ) { 
        
        if(changeState) changeState(StateID::Close);
    }

}
void PlayingState::update(float dt){
    eManager.update(dt);
    cManager.update();
    eManager.garbageCollector();
}
void PlayingState::render(SDL::RendererPtr r){
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255); // RGBA
    SDL::renderClear(r);
    eManager.render(r);
    SDL::renderPresent(r);
}// 
