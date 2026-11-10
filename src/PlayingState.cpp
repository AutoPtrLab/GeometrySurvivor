#include "PlayingState.h"
#include "Components/ComponentsList.h"
#include "Components/HealthComponent.h"
#include "Components/SpellComponent.h"
#include "Game.h"
#include "GameData.h"
#include "RandomUtils.h"
#include "SDL_scancode.h"
#include "SpellRegistry.h"
#include "State.h"
#include <cstdio>

PlayingState::PlayingState(std::function<void(StateID)> chaState, GameData &gData)
    : State(chaState, gData), cManager(eManager.getUpdateVec()), fact(eManager, aiContext, gData) {

    fact.makePlayer([this](Entity &e) { setAsPlayer(e); }, [this]() { setPlayerNull(); }, keyPressedVec);

    fact.makeHexagon();
}

PlayingState::~PlayingState() = default;

void PlayingState::handleEvent(const SDL::Event &e) {

    if (e.type == SDL_QUIT) {
        if (changeState)
            changeState(StateID::Close);
    }
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.scancode == SDL_SCANCODE_LCTRL) {
            startWave();
        } else {
            keyPressedVec.push_back(e);
        }
    }
}
void PlayingState::update(float dt) {

    waveTimer.update(dt);
    if (waveTimer.isReady()) {
        startWave();
    }
    shopTimer.update(dt);
    if (shopTimer.isReady()) {
        changeState(StateID::Shop);
    }
    eManager.flushBuffer();
    // update AIcontext
    aiContext.isPlayerAlive = static_cast<bool>(getPlayer());

    if (getPlayer()) {
        aiContext.playerPos = getPlayer()->getComponent<TransformComponent>()->getPos();

    } else {
        changeState(StateID::Close);

        printf("SCORE: %d\n", score);
        printf("YOU SURVIVED TILL THE %d WAVE\n", this->gameData.wave);
        return;
    }
    eManager.update(dt);
    cManager.update();
}

void PlayingState::render(SDL::RendererPtr r) {

    eManager.render(r);
}

void PlayingState::startWave() {
    gameData.wave++;
    waveTimer.reset();

    int wavePoints = 10 + gameData.wave * 5;
    while (wavePoints >= 3) {

        switch (randomInt(3, 7)) {
        case 3:
            wavePoints -= 3;
            fact.makeTriangule();
            break;
        case 4:
            wavePoints -= 5;
            fact.makeSquare();
            break;
        case 5:
            wavePoints -= 10;
            fact.makePentagon();
            break;
        case 6:
            wavePoints -= 15;
            fact.makeHexagon();
            break;
        case 7:
            wavePoints -= 25;
            fact.makeHeptagon();
            break;
        }
    }
}
