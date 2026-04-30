#pragma once
#include "Entity.h"
#include "infoAI.h"

class EntityManager;

class Factory{
    
    private:
        EntityManager* eManager;
        infoAI& AIcontext;
        Entity& addEntity(int depth);
       
    public:

        Factory(EntityManager& em,infoAI& ctx);
        ~Factory();

        void makePlayer(std::function<void (Entity& e)> funcCreate ,std::function<void ()> funcDestroy, std::vector <SDL::Event> &keyPressedVec);
        
        void makeBullet(Vector2D pos,Vector2D dir);
        void makePiercingBullet(Vector2D pos,Vector2D dir);
        void makeBlast(Vector2D pos);
        void makeIceAura(Vector2D pos);
        void makeFireAura(Vector2D pos);
        void makeThunderAura(Vector2D pos);

        void makeRandomEnemy();

        void update();





};