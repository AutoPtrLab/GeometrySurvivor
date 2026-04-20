#pragma once

#include "State.h"
#include "EntityManager.h"
#include "ColliderManager.h"


class PlayingState: public State{

    private:
        EntityManager eManager;
        ColliderManager cManager;
    public: 

        PlayingState(std::function <void(StateID)> chaState);
        ~PlayingState();
        void handleEvent(const SDL::Event &e) override;
        void update(float dt) override;
        void render(SDL::RendererPtr r) override;

};