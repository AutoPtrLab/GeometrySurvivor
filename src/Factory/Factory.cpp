#include "Factory.h"
#include "Components/ComponentsList.h"
#include "EntityManager.h"


Factory::Factory(EntityManager& em,infoAI& ctx):eManager(&em),AIcontext(ctx){
   
}
Factory::~Factory()=default;

Entity& Factory::addEntity(int depth){
    auto e2=std::make_unique<Entity>(depth);
    auto& e=*e2;
    eManager->addBufferEntity(std::move (e2));
    return e;
}


void Factory::makePlayer(std::function<void (Entity& e)> funcCreate ,std::function<void ()> funcDestroy , std::vector <SDL::Event> &keyPressedVec){

    auto &e=addEntity(2);
    e.addComponent<TransformComponent>(Vector2D{400,20},100.0f) ;
    e.addComponent<SimpleSpriteComponent>(8,5,SDL::Colors::Player);
    e.addComponent<ControllerComponent>(keyPressedVec);
    e.addComponent<PlayerCollider>(4.0f,CollisionLayer::Player,CollisionLayer::None);
    e.addComponent<HealthComponent>(100);
    e.addComponent<PlayerComponent>(funcCreate,funcDestroy);

    e.addComponent<SpellComponent>().addSpell(Spell::Bullet,std::make_unique<BulletSpell>(0.35f,[this](Vector2D initpos,Vector2D dir){
        this->makeBullet(initpos,dir,CollisionLayer::Enemy);
    }));
    e.getComponent<SpellComponent>()->addSpell(Spell::Dash,std::make_unique<DashSpell>());
    e.getComponent<SpellComponent>()->addSpell(Spell::Blast,std::make_unique<CallbackSpell>(3.0f,[this](Vector2D initPos){this->makeBlast(initPos);}));
    e.getComponent<SpellComponent>()->addSpell(Spell::IceAura,std::make_unique<CallbackSpell>(4.0f,[this](Vector2D pos){this->makeIceAura(pos);}));
    e.getComponent<SpellComponent>()->addSpell(Spell::FireAura,std::make_unique<CallbackSpell>(4.0f,[this](Vector2D pos){this->makeFireAura(pos);}));
    e.getComponent<SpellComponent>()->addSpell(Spell::ThunderAura,std::make_unique<CallbackSpell>(5.0f,[this](Vector2D pos){this->makeThunderAura(pos);}));
    e.getComponent<SpellComponent>()->addSpell(Spell::PiercingBullet,std::make_unique<BulletSpell>(1.0f,[this](Vector2D pos,Vector2D dir){this->makePiercingBullet(pos,dir);}));
    e.getComponent<SpellComponent>()->addSpell(Spell::ShotgunBullet,std::make_unique<BulletSpell>(1.5f,[this](Vector2D pos,Vector2D dir){
        this->makeBullet(pos,dir);
        this->makeBullet(pos,Vector2D{dir.x*0.8f,dir.y*1.2f});
        this->makeBullet(pos,Vector2D{dir.x*1.1f,dir.y*1.3f});
        this->makeBullet(pos,Vector2D{dir.x*1.3f,dir.y*0.90f});
        this->makeBullet(pos,Vector2D{dir.x*1.4f,dir.y*1.1f});
        this->makeBullet(pos,Vector2D{dir.x*1.2f,dir.y*0.7f});
        this->makeBullet(pos,Vector2D{dir.x*1.2f,dir.y*1.4f});
        
    }));
    e.getComponent<SpellComponent>()->addSpell(Spell::SpreadBullet,std::make_unique<BulletSpell>(1.5f,[this](Vector2D pos,Vector2D dir){
        this->makeBullet(pos,dir);
        this->makeBullet(pos,Vector2D{dir.x*0.939f-dir.y*0.349f,dir.x*0.349f+dir.y*0.939f});//we rotate 20 grads
        this->makeBullet(pos,Vector2D{dir.x*0.939f-dir.y*-0.349f,dir.x*-0.349f+dir.y*0.939f});
    }));
    e.init();
}
