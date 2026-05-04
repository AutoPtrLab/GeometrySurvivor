#pragma once

#include "SimpleAIComponent.h"
#include "infoAI.h"



class ArcherAIComponent : public SimpleAIComponent {

    private:

        

    public:

        ArcherAIComponent(infoAI &info);

        void update(float dt) override;

};