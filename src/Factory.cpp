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
        //maybe change if the bullet receive if its an enemy bullet or a player bullet
        auto& e=addEntity(5);


        e.addComponent<TransformComponent>(pos);
        e.getComponent<TransformComponent>()->setVel(dir*150.0f);
        e.addComponent<SimpleSpriteComponent>(2,3,SDL::Colors::NeonPink);
        e.addComponent<BulletCollider>(3.0f,CollisionLayer::Spell,CollisionLayer::Enemy);
        e.addComponent<LifeTimeComponent>(5.0f); 
        e.init();
}   

void Factory::makeRandomEnemy(){

    auto& e=addEntity(3);
    e.addComponent<TransformComponent>(randomSpawnPos(WIDTH,HEIGHT),randomFloat(30,60));
    int rad=randomInt(5,10);//radius of the enemy
    auto color=SDL::Color{static_cast<Uint8>(randomInt(0,255)),static_cast<Uint8>(randomInt(0,255)),static_cast<Uint8>(randomInt(0,255)),255};
    e.addComponent<SimpleSpriteComponent>(rad,randomInt(3,10),color);
    e.addComponent<EnemyCollider>(rad,CollisionLayer::Enemy,CollisionLayer::Player);
    e.addComponent<HealthComponent>(rad*10,0.2f);//no inviTime for the enemies
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.init();
}

void Factory::makeBlast(Vector2D pos){

    auto&e = addEntity(1);//making the first thing visible
     e.addComponent<TransformComponent>(pos);
     e.addComponent<SpellCollider>(40.0f,CollisionLayer::Spell,CollisionLayer::Enemy);
     e.addComponent<LifeTimeComponent>(0.5f);
     e.addComponent<SimpleSpriteComponent>(40.0f,20,SDL::Colors::voidDust);
     e.init();
}


void Factory::makePlayer(std::function<void (Entity& e)> funcCreate ,std::function<void ()> funcDestroy , std::vector <SDL::Event> &keyPressedVec){

    auto &e=addEntity(2);
    e.addComponent<TransformComponent>(Vector2D{400,20},100.0f) ;
    e.addComponent<SimpleSpriteComponent>(8,5,SDL::Colors::Electric);
    e.addComponent<ControllerComponent>(keyPressedVec);
    e.addComponent<PlayerCollider>(4.0f,CollisionLayer::Player,CollisionLayer::None);
    e.addComponent<HealthComponent>(100);
    e.addComponent<PlayerComponent>(funcCreate,funcDestroy);
    e.addComponent<SpellComponent>().addSpell(Spell::Bullet,std::make_unique<BulletSpell>([this](Vector2D initpos,Vector2D dir){
        this->makeBullet(initpos,dir);
    }));
    e.getComponent<SpellComponent>()->addSpell(Spell::Dash,std::make_unique<DashSpell>());
    e.getComponent<SpellComponent>()->addSpell(Spell::Blast,std::make_unique<BlastSpell>([this](Vector2D initPos){this->makeBlast(initPos);}));
    e.init();
}