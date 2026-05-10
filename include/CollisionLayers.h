#pragma once
#include <cstdint>

namespace CollisionLayer {
enum Type : uint8_t { // bit mask to resolve collisions

    None = 0,
    Player = 1 << 0,
    Enemy = 1 << 1,
    Spell = 1 << 2

};
}
