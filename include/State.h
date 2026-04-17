#pragma once 

#include "SDL_wrapper.h"
#include <functional>


//State identificator
enum class StateID {
    None,//ID that represents a null State
    Close, //ID that represents exiting the game
    Playing,
    Menu
};
 //Interface for the State 

class State{

    protected:
        
        std::function<void(StateID id)> changeState; 

    public:

        State(std::function <void(StateID)> chaState):changeState(chaState){}; // custom constructor for all the States
        virtual ~State()=default;
        virtual void handleEvent(const SDL::Event &e)=0;
        virtual void update(float dt)=0;
        virtual void render(SDL::RendererPtr r)=0;

};

