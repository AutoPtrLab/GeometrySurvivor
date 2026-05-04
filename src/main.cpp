
#include "Game.h"

int main(int /*argc*/,char* /*argv*/[]){
    
   SDL::init();
    Game g;
    g.init();
    SDL::quit();
}