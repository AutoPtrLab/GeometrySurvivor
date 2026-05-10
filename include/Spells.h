#pragma once

#include "Components/HealthComponent.h"
#include "Components/TransformComponent.h"
#include "Entity.h"
#include "Timer.h"

class ISpell {

  protected:
    Timer cooldown; // we have to reset each time we call
  public:
    ISpell(float cooldown) : cooldown(cooldown) {}
    virtual ~ISpell() = default;
    virtual void cast(Entity &e, Vector2D dir) = 0;
    virtual void update(Entity &e, float dt) { cooldown.update(dt); };
    virtual void render(Entity &e, SDL::RendererPtr r) {}
};

class BulletSpell : public ISpell {

  private:
    std::function<void(Vector2D initPos, Vector2D dir)> castBullet;

  public:
    BulletSpell(float rechargeTime, std::function<void(Vector2D initPos, Vector2D dir)> func) : ISpell(rechargeTime), castBullet(func) {}
    void cast(Entity &e, Vector2D dir) override {
        if (cooldown.isReady()) {
            if (castBullet)
                castBullet(e.getComponent<TransformComponent>()->getPos(), dir);
            cooldown.reset();
        }
    }
};

class DashSpell : public ISpell {

  private:
    Timer dashTimer{.2f}; // how much time does the dash lasts
    bool dashing = false;
    float prevSpeed = 0.0f;

  public:
    DashSpell() : ISpell(1.0f) {}
    void cast(Entity &e, Vector2D dir) override {
        if (cooldown.isReady()) {
            auto *tc = e.getComponent<TransformComponent>();
            prevSpeed = tc->getSpeed();
            tc->setSpeed(prevSpeed * 3.0f);
            dashing = true;
            cooldown.reset();
            dashTimer.reset();
        }
    }
    void update(Entity &e, float dt) override {
        if (dashing) {
            dashTimer.update(dt);
        } else {
            cooldown.update(dt);
        }

        if (dashTimer.isReady()) {

            dashTimer.reset();
            auto *tc = e.getComponent<TransformComponent>();
            Vector2D dir = tc->getVel().getNormalized();
            tc->setSpeed(prevSpeed);
            dashing = false;
        }
    }
};

class CallbackSpell : public ISpell { // spell for which we only call a lambda

  private:
    std::function<void(Vector2D pos)> callback;

  public:
    CallbackSpell(float rechargeTime, std::function<void(Vector2D pos)> c) : ISpell(rechargeTime), callback(c) {}
    void cast(Entity &e, Vector2D dir) override {
        if (cooldown.isReady()) {

            if (callback) {
                callback(dir);
            }
            cooldown.reset();
        }
    }
};
