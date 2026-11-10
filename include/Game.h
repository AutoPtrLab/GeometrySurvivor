#pragma once

#include "GameData.h"
#include "SDL_wrapper.h"
#include "State.h"

extern int score;

class Game {

  private:
    SDL::Window window;
    SDL::Renderer renderer;

    bool running = false;

    std::unique_ptr<State> state;
    StateID nextState; // variable that holds the next state

    GameData gameData;

  public:
    Game();
    ~Game();
    void init();
    void updateState();
};
