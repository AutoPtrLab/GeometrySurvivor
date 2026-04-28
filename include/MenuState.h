#pragma once
#include "State.h"
#include "SDL_wrapper.h"

class MenuState: public State{

    private:

        

    public:
        
        MenuState(std::function <void(StateID)> chaState);
        ~MenuState();
        void handleEvent(const SDL::Event &e) override;
        void update(float dt) override;
        void render(SDL::RendererPtr r) override;
};