#include "Components/ComponentsList.h"
#include "Components/HealthComponent.h"
#include "EntityManager.h"
#include "Factory.h"

//================================================
//~~~~~~~~~~~~~~SPELLS~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//================================================

void Factory::makeBullet(Vector2D pos, Vector2D dir, CollisionLayer::Type mask) {
    // maybe change if the bullet receive if its an enemy bullet or a player bullet
    auto &e = addEntity(5);

    e.addComponent<TransformComponent>(pos).setSpeed(150.0f);
    e.getComponent<TransformComponent>()->setDir(dir);
    e.addComponent<SimpleSpriteComponent>(2, 3, SDL::Colors::NeonPink);
    e.addComponent<BulletCollider>(3.0f, CollisionLayer::Spell, mask);
    e.addComponent<LifeTimeComponent>(5.0f);
    e.init();
}
void Factory::makePiercingBullet(Vector2D pos, Vector2D dir) {
    auto &e = addEntity(5);
    e.addComponent<TransformComponent>(pos).setSpeed(150.0f);
    e.getComponent<TransformComponent>()->setDir(dir);
    e.addComponent<SimpleSpriteComponent>(2, 3, SDL::Colors::NeonPurple);
    e.addComponent<SpellCollider>(
        3.0f, CollisionLayer::Spell, CollisionLayer::Enemy,
        [this](Entity *e) { // we use an spell collider so it doesnt dissapear
            if (e->getComponent<HealthComponent>()) {
                e->getComponent<HealthComponent>()->getHit(10);
            }
        },
        0.05f);
    e.addComponent<LifeTimeComponent>(5.0f);
    e.init();
}
void Factory::makeBlast(Vector2D pos) {

    auto &e = addEntity(1); // making the first thing visible
    e.addComponent<TransformComponent>(pos);
    e.addComponent<SpellCollider>(40.0f, CollisionLayer::Spell, CollisionLayer::Enemy, [this](Entity *e) {
        if (e->getComponent<HealthComponent>()) {
            e->getComponent<HealthComponent>()->getHit(10);
        }
    });
    e.addComponent<LifeTimeComponent>(1.0f);
    e.addComponent<SimpleSpriteComponent>(40.0f, 20, SDL::Colors::VoidDust);
    e.init();
}
void Factory::makeIceAura(Vector2D pos) {

    auto &e = addEntity(5);
    e.addComponent<TransformComponent>(pos, 170.0f);
    e.addComponent<SpellCollider>(40.0f, CollisionLayer::Spell, CollisionLayer::Enemy,
                                  [this](Entity *e) { e->getComponent<HealthComponent>()->setStatus(&Status::Frozen, 2.0f); });
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.addComponent<LifeTimeComponent>(3.0f);
    e.addComponent<SimpleSpriteComponent>(40.0f, 6, SDL::Colors::Ice);
    e.init();
}

void Factory::makeFireAura(Vector2D pos) {

    auto &e = addEntity(5);
    e.addComponent<TransformComponent>(pos, 170.0f);
    e.addComponent<SpellCollider>(40.0f, CollisionLayer::Spell, CollisionLayer::Enemy,
                                  [this](Entity *e) { e->getComponent<HealthComponent>()->setStatus(&Status::Burn, 2.0f); });
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.addComponent<LifeTimeComponent>(3.0f);
    e.addComponent<SimpleSpriteComponent>(40.0f, 6, SDL::Colors::Fire);
    e.init();
}

void Factory::makeThunderAura(Vector2D pos) {

    auto &e = addEntity(5);
    e.addComponent<TransformComponent>(pos, 170.0f);
    e.addComponent<SpellCollider>(20.0f, CollisionLayer::Spell, CollisionLayer::Enemy,
                                  [this](Entity *e) { e->getComponent<HealthComponent>()->setStatus(&Status::Stun, 1.0f); });
    e.addComponent<SimpleAIComponent>(AIcontext);
    e.addComponent<LifeTimeComponent>(3.0f);
    e.addComponent<SimpleSpriteComponent>(20.0f, 8, SDL::Colors::Electric);
    e.init();
}

void Factory::makeExplosion(Vector2D pos, float rad, CollisionLayer::Type mask) {

    auto &e = addEntity(5);
    e.addComponent<TransformComponent>(pos, 170.0f);
    e.addComponent<SpellCollider>(
        rad, CollisionLayer::Spell, mask,
        [this](Entity *e) {
            e->getComponent<HealthComponent>()->setStatus(&Status::Stun, 1.0f);
            e->getComponent<HealthComponent>()->getHit(5);
        },
        0.1f);
    e.addComponent<LifeTimeComponent>(0.25f);
    e.addComponent<SimpleSpriteComponent>(rad, 8, SDL::Colors::Electric);
    e.init();
}

void Factory::makeInferno(Vector2D pos, CollisionLayer::Type mask) {

    auto &e = addEntity(1); // making the first thing visible
    e.addComponent<TransformComponent>(pos);
    e.addComponent<SpellCollider>(
        1.0f, CollisionLayer::Spell, mask,
        [this](Entity *e) {
            if (e->getComponent<HealthComponent>()) {
                e->getComponent<HealthComponent>()->getHit(10);
                e->getComponent<HealthComponent>()->setStatus(&Status::Burn, 1.0f);
            }
        },
        0.2f);
    e.addComponent<LifeTimeComponent>(1.0f);
    e.addComponent<SimpleSpriteComponent>(1.0f, 12, SDL::Colors::Inferno);
    e.addComponent<ScaleComponent>(25.0f, 10.0f);
    e.init();
}
