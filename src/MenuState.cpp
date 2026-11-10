#include "MenuState.h"
#include "GameData.h"
#include "SDL_scancode.h"
#include "State.h"
#include <cstdio>

MenuState::MenuState(std::function<void(StateID)> chaState, GameData &gData) : State(chaState, gData) {
    printf("\033[2J\033[1;1H");
    printf("\n");
    printf("=========================================\n");
    printf("         GEOMETRY SURVIVOR            \n");
    printf("=========================================\n");

    printf("\n");
    printf("Welcome, traveler. What would you like to do?\n");
    printf("\n");
    printf("  1. Start Game\n");
    printf("  2. Quit Game\n");
    printf("  3. Controls and info\n");
    printf("\n");
}

MenuState::~MenuState() = default;

void printControls() {
    printf("\n=========================================\n");
    printf("              GEOMETRY SURVIVOR          \n");
    printf("=========================================\n");
    printf("  Mouse ......... move (the player follows the cursor)\n");
    printf("  Z / X ......... aimed spells (shot toward the mouse)\n");
    printf("  C / V ......... area spells (cast around you)\n");
    printf("  Left Ctrl ..... call the next wave early\n");
    printf("-----------------------------------------\n");
    printf("  In the shop: Z/X/C/V equip the spell in that slot,\n");
    printf("               5 upgrades the stat\n");
    printf("=========================================\n\n");
    printf("  Press 1 to play or 2 to quit the Game\n");
}
void MenuState::handleEvent(const SDL::Event &e) {
    if (e.type == SDL_QUIT) {

        if (changeState)
            changeState(StateID::Close);
    }
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_1:
            changeState(StateID::Playing);
            break;
        case SDL_SCANCODE_2:
            changeState(StateID::Close);
            break;
        case SDL_SCANCODE_3:
            printControls();
            break;
        default:
            break;
        }
    }
}
void MenuState::update(float dt) {}

void MenuState::render(SDL::RendererPtr r) {}
