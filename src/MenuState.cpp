#include "MenuState.h"

MenuState::MenuState(std::function<void(StateID)> chaState) : State(chaState) {
    printf("PRESS z TO START\n");
}

MenuState::~MenuState() = default;

void MenuState::handleEvent(const SDL::Event &e) {
    if (e.type == SDL_QUIT) {

        if (changeState)
            changeState(StateID::Close);
    }
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_Z:
            changeState(StateID::Playing);
            break;
        }
    }
}
void MenuState::update(float dt) {}

void MenuState::render(SDL::RendererPtr r) {}
