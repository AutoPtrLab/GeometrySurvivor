#pragma once

namespace CollisionLayer{
    enum Type : uint16_t{//bit mask to resolve collisions

    None = 0,
    Player=1<<0,
    Enemy = 1<<1,
    Spell= 1<<2


};
};