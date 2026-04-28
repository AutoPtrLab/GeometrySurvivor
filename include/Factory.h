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
        
        
        void makeBullet(Vector2D pos,Vector2D dir);
        void makeBlast(Vector2D pos);

        void makeRandomEnemy();

        void update();





};