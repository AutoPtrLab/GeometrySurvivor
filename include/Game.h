#pragma once

#include "SDL_wrapper.h"
#include "State.h"

class Game{

    private:

        SDL::Window window;
        SDL::Renderer renderer;
        
        bool running=false;

        std::unique_ptr<State> currentState;
        StateID nextState;//variable that holds the next state
    
    public:
        Game();
        ~Game();
        void init();
        void updateState();
        

};