#pragma once
#include "Components/SimpleAIComponent.h"

class MageAIComponent : public SimpleAIComponent {

  public:
    MageAIComponent(infoAI &info);
    void update(float dt) override;
};
