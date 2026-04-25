#include "Factory.h"
#include "Components/ComponentsList.h"
#include "EntityManager.h"


Factory::Factory(EntityManager& em,infoAI& ctx):eManager(&em),AIcontext(ctx){}
Factory::~Factory()=default;

Entity& Factory::addEntity(int depth){
    auto e2=std::make_unique<Entity>(depth);
    auto& e=*e2;
    eManager->addBufferEntity(std::move (e2));
    return e;
}

void Factory::makeBullet(Vector2D pos,Vector2D dir){
    
        auto& e=addEntity(5);


        e.addComponent<TransformComponent>(pos);
        e.getComponent<TransformComponent>()->setVel(dir*150.0f);
        e.addComponent<SimpleSpriteComponent>(2,3,SDL::Colors::NeonPink);
        e.addComponent<ColliderComponent>(3,Faction::Bullet);
        e.addComponent<LifeTimeComponent>(5.0f); 
}   


