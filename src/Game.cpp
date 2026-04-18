#include "Game.h"
#include "PlayingState.h"

Game::Game():window(SDL::CreateWindow()),renderer(SDL::CreateRenderer(window)){}

Game::~Game()=default;

void Game::init(){

    running=true;

    currentState=std::make_unique<PlayingState>([this](StateID id){ nextState=id;});

    Uint64 lastTime = SDL_GetPerformanceCounter();  

    float accumulator = 0.0f;
    constexpr float FIXED_DT=1.0f/(60.0f);
    
    while(running){
 
        //polling events
        SDL::Event e;

        while(SDL_PollEvent(&e)){
            currentState->handleEvent(e);
            
        }

        //getting delta Time
        Uint64 now = SDL_GetPerformanceCounter();

        float dt = (float)(now - lastTime) / (float)SDL_GetPerformanceFrequency();
        lastTime = now;
        if (dt > 0.05f) dt = 0.05f; // delta Time clamp for lagspikes

        accumulator += dt;
        while (accumulator >= FIXED_DT) {
            currentState->update(FIXED_DT);
            accumulator -= FIXED_DT;
        }
       
        //fps , may remove later
        float fps = 1.0f / dt;
        SDL_SetWindowTitle(window.get(), ("GeometrySurvivor | FPS: " + std::to_string(static_cast<int>(fps))).c_str());

        
        updateState();
        currentState->render(renderer.get());
    }
}



void Game::updateState(){

    if(nextState != StateID::None ){
        
        auto stateCallback = [this](StateID id){ nextState=id;} ; //callback 

        switch (nextState)
        {
        case StateID::Close:
            
            running=false;
            break;
        case StateID::Playing:
            currentState=std::make_unique<PlayingState>(stateCallback);
            break;
        default:
            break;
        }

        nextState = StateID::None;//no queued State
    }

}