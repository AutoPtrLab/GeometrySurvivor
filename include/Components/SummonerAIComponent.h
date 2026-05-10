#pragma once
#include "SimpleAIComponent.h"
#include "infoAI.h"

class SummonerAIComponent : public SimpleAIComponent {

  public:
    SummonerAIComponent(infoAI &info);
    void update(float dt) override;
};
