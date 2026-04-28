#include "PlayingState.h"
#include "Components/ComponentsList.h"

PlayingState::PlayingState(std::function <void(StateID)> chaState):State(chaState),cManager(eManager.getUpdateVec()),fact(eManager,aiContext){
    
    

    //inicialitation of entities( factory neede ASAP)
    auto &e=eManager.addEntity(1);
    e.addComponent<TransformComponent>(Vector2D{400,20},100.0f) ;
    e.addComponent<SimpleSpriteComponent>(8,5,SDL::Colors::Electric);
    e.addComponent<ControllerComponent>(keyPressedVec);
    e.addComponent<ColliderComponent>(4.0f,Faction::Player);
    e.addComponent<HealthComponent>(100);
    e.addComponent<PlayerComponent>([this](Entity& e){setAsPlayer(e);},[this](){setPlayerNull();});

    e.addComponent<SpellComponent>().addSpell(Spell::Bullet,std::make_unique<BulletSpell>([this](Vector2D initpos,Vector2D dir){
        this->fact.makeBullet(initpos,dir);
    }));
    e.getComponent<SpellComponent>()->addSpell(Spell::Dash,std::make_unique<DashSpell>());
   // e.addComponent<SpellComponent>().addSpell(SpellType::Dash,[&e](Vector2D pos,Vector2D dir){});
    e.init();
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
