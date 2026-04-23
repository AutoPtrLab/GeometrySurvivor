#include "PlayingState.h"
#include "Components/ComponentsList.h"

PlayingState::PlayingState(std::function <void(StateID)> chaState):State(chaState),cManager(eManager.getUpdateVec()){
    
    

    //inicialitation of entitys( factory neede ASAP)
    auto &e=eManager.addEntity(1);
    e.addComponent<TransformComponent>(Vector2D{400,20}) ;
    e.addComponent<SimpleSpriteComponent>(8,5,SDL::Colors::Electric);
    e.addComponent<ControllerComponent>(70.0f);
    e.addComponent<ColliderComponent>(4.0f,Faction::Player);
    e.addComponent<HealthComponent>(100);
    e.addComponent<PlayerComponent>([this](Entity& e){setAsPlayer(e);},[this](){setPlayerNull();});
    e.init();
    
     
   
    
    auto &e2=eManager.addEntity(2);
    e2.addComponent<TransformComponent>(Vector2D{50,50}) ;
    e2.addComponent<SimpleSpriteComponent>(4,10,SDL::Colors::Pumpkin);
    e2.addComponent<SimpleAIComponent>(aiContext,30.0f);
    e2.addComponent<ColliderComponent>(4.0f,Faction::Enemy);
    e2.init(); 
     auto &e3=eManager.addEntity(3);
    e3.addComponent<TransformComponent>(Vector2D{120,90}) ;
    e3.addComponent<SimpleSpriteComponent>();
    e3.addComponent<SimpleAIComponent>(aiContext,30.0f);
    e3.addComponent<ColliderComponent>(4.0f,Faction::Enemy);
    e3.init(); 
 
}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const SDL::Event &e){
    
    if (e.type == SDL_QUIT ) { 
        
        if(changeState) changeState(StateID::Close);
    }

}
void PlayingState::update(float dt){

    //update AIcontext
    aiContext.isPlayerAlive= static_cast<bool> (getPlayer());
    if(getPlayer()){
        aiContext.playerPos= getPlayer()->getComponent<TransformComponent>()->getPos();
    }
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
