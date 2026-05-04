#pragma once
#include "Entity.h"
#include "infoAI.h"
#include "CollisionLayers.h"
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
        


        //========SPELLS=======
        void makeBullet(Vector2D pos,Vector2D dir,CollisionLayer::Type mask=CollisionLayer::Enemy);
        void makePiercingBullet(Vector2D pos,Vector2D dir);
        void makeBlast(Vector2D pos);
        void makeExplosion(Vector2D,float rad,CollisionLayer::Type mask=CollisionLayer::Enemy);//has no lingering efeects like blast
        void makeIceAura(Vector2D pos);
        void makeFireAura(Vector2D pos);
        void makeThunderAura(Vector2D pos);
        void makeInferno(Vector2D pos,CollisionLayer::Type mask=CollisionLayer::Enemy);
        //==========ENEMIES============
        void makeRandomEnemy();//
        void makeMiniBomber(Vector2D pos);

        void makeTriangule();//zombie enemy
        void makeSquare();//dasher enemy
        void makePentagon();//lasser enemy
        void makeHexagon();//summoner enemy
        void makeHeptagon();//area wizard enemy
        


        void update();





};