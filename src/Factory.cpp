#include "Factory.h"
#include "Components/ComponentsList.h"
#include "EntityManager.h"
#include <cstdlib>
#include <ctime>

//HELPER FUNCTIONS TO USE RANDOMIZE NUMBERS

int randomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

float randomFloat(float min, float max) {
    return min + (float)rand() / RAND_MAX * (max - min);
}

Vector2D randomSpawnPos(float screenW, float screenH, float margin = 50.0f) {
    switch(randomInt(0, 3)) {
        case 0: 
            return {randomFloat(0, screenW), -margin};
        case 1: 
            return {randomFloat(0, screenW), screenH + margin};
        case 2: 
            return {-margin, randomFloat(0, screenH)};
        case 3: 
            return {screenW + margin, randomFloat(0, screenH)};
    }
        return Vector2D{0,0};
}

Factory::Factory(EntityManager& em,infoAI& ctx):eManager(&em),AIcontext(ctx){
    srand(time(0));//initialize the random function
}
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
        e.init();
}   

void Factory::makeRandomEnemy(){

    auto& e=addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH,HEIGHT),randomFloat(30,60));
    int rad=randomInt(5,10);//radius of the enemy
    auto color=SDL::Color{static_cast<Uint8>(randomInt(0,255)),static_cast<Uint8>(randomInt(0,255)),static_cast<Uint8>(randomInt(0,255)),255};
    e.addComponent<SimpleSpriteComponent>(rad,randomInt(3,10),color);
    e.addComponent<ColliderComponent>(rad,Faction::Enemy);
    e.addComponent<HealthComponent>(rad*10,0.0f);//no inviTime for the enemies
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.init();
}

void Factory::makeBlast(Vector2D pos){

    auto&e = addEntity(1);//making the first thing visible
     e.addComponent<TransformComponent>(pos);
     e.addComponent<ColliderComponent>(20.0f,Faction::Spell);
     e.addComponent<LifeTimeComponent>(0.2f);
     e.addComponent<SimpleSpriteComponent>(20.0f,12,SDL::Colors::voidDust);
}
