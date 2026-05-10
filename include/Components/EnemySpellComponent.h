#pragma once
#include "Components/Component.h"
#include "Spells.h"
#include <array>

namespace EnemySpell {
enum SpellSlot {

    Primary,
    Secondary,
    Special
};
}
constexpr size_t MAX_ENEMY_SPELLS = 3;
class EnemySpellComponent : public Component<EnemySpellComponent> {

  private:
    std::array<std::unique_ptr<ISpell>, MAX_ENEMY_SPELLS> spells;

  public:
    EnemySpellComponent();

    void addSpell(EnemySpell::SpellSlot slot, std::unique_ptr<ISpell> ptr); // the making of the spells is made in the factory
    void castSpell(EnemySpell::SpellSlot slot, Vector2D pos);

    void update(float dt) override;
    void render(SDL::RendererPtr r) override;
};
