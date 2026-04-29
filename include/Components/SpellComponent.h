#pragma once
#include "Component.h"
#include "array"
#include "functional"
#include "Vector2D.h"
#include "Spells.h"

namespace Spell{
    enum  SpellType{
        Bullet,
        Dash,
        Blast
    };
}

constexpr size_t MaxSpells=32;
class SpellComponent : public Component<SpellComponent>{

    private:

        std::array<std::unique_ptr<ISpell>,MaxSpells> spells; 
    

    public:

        SpellComponent();
        ~SpellComponent();

        void addSpell(Spell::SpellType type,std::unique_ptr<ISpell> ptr);//the making of the spells is made in the factory 
        void castSpell(Spell::SpellType type,Vector2D dir);//if thre is no 

        void update(float dt) override;
        void render(SDL::RendererPtr r) override;


};