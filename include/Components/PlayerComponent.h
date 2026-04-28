#pragma once

#include "Component.h"
#include <functional>



class Entity;


class PlayerComponent : public Component<PlayerComponent> {

    private:        
        
        std::function<void()> destroyPlayer; //automatically sets null the player reference
        std::function<void(Entity& e)> setPlayer;
    public:

        PlayerComponent(std::function<void(Entity& player)> setPlayerFunc,std::function<void()> destPlayerFunc);
        ~PlayerComponent() override;

        void init() override;

        void update(float dt) override;
        void render(SDL::RendererPtr r)override;

};