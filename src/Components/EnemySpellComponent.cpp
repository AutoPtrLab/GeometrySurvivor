#include "Components/EnemySpellComponent.h"

EnemySpellComponent::EnemySpellComponent() {}

void EnemySpellComponent::addSpell(EnemySpell::SpellSlot slot, std::unique_ptr<ISpell> ptr) {
    spells[slot] = std::move(ptr);
}

void EnemySpellComponent::castSpell(EnemySpell::SpellSlot slot, Vector2D pos) {
    if (auto &spell = spells[slot])
        spell->cast(*this->entity, pos);
}

void EnemySpellComponent::update(float dt) {

    for (auto const &s : spells) {
        if (!s)
            continue;
        s->update(*this->entity, dt);
    }
}

void EnemySpellComponent::render(SDL::RendererPtr r) {

    for (auto const &s : spells) {
        if (!s)
            continue;
        s->render(*this->entity, r);
    }
}
