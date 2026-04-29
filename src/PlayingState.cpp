#include "PlayingState.h"
#include "Components/ComponentsList.h"

PlayingState::PlayingState(std::function <void(StateID)> chaState):State(chaState),cManager(eManager.getUpdateVec()),fact(eManager,aiContext){
    
    

    
    fact.makePlayer([this](Entity& e){setAsPlayer(e);},[this](){setPlayerNull();},keyPressedVec);

    
    for(int i=0;i<9;i++){
        fact.makeRandomEnemy();
    }
 
 
}

PlayingState::~PlayingState()=default;

void PlayingState::handleEvent(const SDL::Event &e){
    
    if (e.type == SDL_QUIT ) { 
        
        if(changeState) changeState(StateID::Close);
    }
    if(e.type == SDL_KEYDOWN){
        keyPressedVec.push_back(e);
    }

}
void PlayingState::update(float dt){
    eManager.flushBuffer();
    //update AIcontext
    aiContext.isPlayerAlive= static_cast<bool> (getPlayer());
    if(getPlayer()){
        aiContext.playerPos= getPlayer()->getComponent<TransformComponent>()->getPos();
    }
    eManager.update(dt);
    cManager.update();
}
void PlayingState::render(SDL::RendererPtr r){

    eManager.render(r);
}
