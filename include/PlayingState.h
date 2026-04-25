#pragma once

#include "State.h"
#include "EntityManager.h"
#include "ColliderManager.h"
#include "infoAI.h"
#include "Factory.h"

class PlayingState: public State{

    private:
        EntityManager eManager;
        ColliderManager cManager;
        Factory fact;

        std::vector<SDL_Event> keyPressedVec;
        infoAI aiContext;
        Entity* player = nullptr; //reference to the player
         
    public: 

        PlayingState(std::function <void(StateID)> chaState);
        ~PlayingState();
        void handleEvent(const SDL::Event &e) override;
        void update(float dt) override;
        void render(SDL::RendererPtr r) override;

        infoAI getAIContext()const {return aiContext;}
        void setAsPlayer(Entity &player){this->player=&player;} //Selecting an entity to be a player+
        void setPlayerNull(){player=nullptr;}
        Entity* getPlayer() const {return player;}

};