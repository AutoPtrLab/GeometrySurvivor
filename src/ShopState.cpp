#include "ShopState.h"
#include "RandomUtils.h"
#include "SDL_keycode.h"
#include "SDL_scancode.h"
#include "SDL_wrapper.h"
#include "SpellStats.h"
#include "State.h"

#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <vector>
static constexpr const char *slotKeys[4] = {"Z", "X", "C", "V"};
inline bool isAimedSpell(int id) {
    switch (id) {
    case 0:
    case 1:
    case 6:
    case 7:
    case 8:
        return true;
    default:
        return false;
    }
}
ShopState::ShopState(std::function<void(StateID)> chaState, GameData &gData) : State(chaState, gData) {}

void ShopState::update(float dt) {
    if (waitingInput)
        return;

    // std::vector<int> possibleSpells = {};
    // for (int i = 0; i < SpellPresets::allSpells.size(); i++) {
    //     possibleSpells.push_back(i); // we make a vector with the numbers from 1 to ...
    // }

    // for (int i = 0; i < 4; i++) {
    //     int randomIndex = randomInt(0, possibleSpells.size() - 1);
    //     spellsSelected[i] = possibleSpells[randomIndex];            // choosing a random index of the vector that represent every spell the player can get
    //     possibleSpells.erase(possibleSpells.begin() + randomIndex); // we destroy the index so it cant show up again
    // }
    std::vector<int> aimed, area;
    for (int i = 0; i < static_cast<int>(SpellPresets::allSpells.size()); i++)
        (isAimedSpell(i) ? aimed : area).push_back(i);

    auto pickFrom = [](std::vector<int> &pool) {
        int idx = randomInt(0, static_cast<int>(pool.size()) - 1);
        int id = pool[idx];
        pool.erase(pool.begin() + idx);
        return id;
    };

    spellsSelected[0] = pickFrom(aimed); // Z
    spellsSelected[1] = pickFrom(aimed); // X
    spellsSelected[2] = pickFrom(area);  // C
    spellsSelected[3] = pickFrom(area);  // V
    const auto &aS = SpellPresets::allSpells;

    statSelected = randomInt(0, StatsPresets::statNum - 1);

    // cleaning up the terminal

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
    printf("\n=========================================\n");
    printf("               MAGIC SHOP                \n");
    printf("=========================================\n");
    printf("Choose a spell to upgrade your power!\n\n");

    for (int i = 0; i < 4; i++) {
        int id = spellsSelected[i];
        const auto &spell = aS[id];
        int level = gameData.spellReg.getSpellLevel(id);
        std::string safeName(spell.name);

        // Print the spell header (e.g., 1. Fire Aura)
        printf("%s. [%s]\n", slotKeys[i], safeName.c_str());

        // Print its stats formatted in columns
        if (level == 0) {
            printf("   Status:locked\n");
            printf("   Base Damage: %-4d \n", spell.damage);
            printf("   Base Cooldown:    %.2fs\n", spell.rechargeTime);
            printf("\n");

        } else {
            printf("   Status:Unlocked lvl:%-4d\n", level);
            printf("   Damage: %-4d (Upgrade: +%d)\n", spell.damage + spell.damageUpgrade * spell.level, spell.damageUpgrade);
            printf("   Cooldown:    %.2fs (Upgrade: -%.2fs)\n", spell.rechargeTime - spell.rechargeTimeUpgrade * spell.level, spell.rechargeTimeUpgrade);

            printf("\n");
        }
    }
    const auto &s = StatsPresets::allStats[statSelected];
    std::string safeName(s.name);
    int stat_level = gameData.getInfo<int>(safeName).value_or(s.level);

    printf("B. [%s]\n", safeName.c_str());
    printf("    lvl:%-4d\n", stat_level);
    printf("    Value:  %g(Upgrade:  +%g)\n", s.stat, s.statUpgrade);

    printf("-----------------------------------------\n");
    printf("");

    // we wait for the input
    waitingInput = true;
}

void ShopState::handleEvent(const SDL::Event &e) {

    if (e.type == SDL_QUIT) {
        if (changeState)
            changeState(StateID::Close);
        return;
    }

    if (e.type == SDL_KEYDOWN) {
        int option = -1;
        const auto &stat = StatsPresets::allStats[statSelected];

        switch (e.key.keysym.scancode) {
        case SDL_SCANCODE_Z:
            option = 0;
            break;
        case SDL_SCANCODE_X:
            option = 1;
            break;
        case SDL_SCANCODE_C:
            option = 2;
            break;
        case SDL_SCANCODE_V:
            option = 3;
            break;
        case SDL_SCANCODE_B: {
            std::string statName{stat.name};
            int currentLevel = gameData.getInfo<int>(statName).value_or(stat.level);
            gameData.addInfo(statName, currentLevel + 1);
            waitingInput = false;
            this->changeState(StateID::Playing);
            return;
        }
        case SDL_SCANCODE_SPACE:
            this->changeState(StateID::Playing);
        default:
            return;
        }

        int spellID = spellsSelected[option];
        auto targetSlot = static_cast<Spell::SpellSlot>(option);
        auto &reg = gameData.spellReg;

        reg.levelUpSpell(spellID);

        for (int i = 0; i < 4; i++) {
            auto slot = static_cast<Spell::SpellSlot>(i);
            if (slot != targetSlot && reg.getEquippedSpell(slot) == spellID) {
                reg.equipSpell(slot, reg.getEquippedSpell(targetSlot));
                break;
            }
        }
        reg.equipSpell(targetSlot, spellID);

        waitingInput = false;
        this->changeState(StateID::Playing);
    }
}

void ShopState::render(SDL::RendererPtr r) {}
