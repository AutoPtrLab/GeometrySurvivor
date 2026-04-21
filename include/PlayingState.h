#pragma once

#include "State.h"
#include "EntityManager.h"
#include "ColliderManager.h"
#include "infoAI.h"

class PlayingState: public State{

    private:
        EntityManager eManager;
        ColliderManager cManager;

        infoAI aiContext;
        Entity* player = nullptr; //reference to the player
         
    public: 

        PlayingState(std::function <void(StateID)> chaState);
        ~PlayingState();
        void handleEvent(const SDL::Event &e) override;
        void update(float dt) override;
        void render(SDL::RendererPtr r) override;

        void setAsPlayer(Entity &player){this->player=&player;} //Selecting an entity to be a player+
        void setPlayerNull(){player=nullptr;}
        Entity* getPlayer() const {return player;}

};