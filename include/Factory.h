#pragma once
#include "Entity.h"
#include "infoAI.h"

class EntityManager;

class Factory{
    
    private:
        EntityManager* eManager;
        infoAI& AIcontext;
       
    public:

        Factory(EntityManager& em,infoAI& ctx);
        ~Factory();
        
        Entity& addEntity(int depth);
        void makeBullet(Vector2D pos,Vector2D dir);

        void update();





};