#pragma once

#include "Components/Component.h"

class ColliderComponent;
class SimpleSpriteComponent;



class ScaleComponent : public Component<ScaleComponent>{

    private:

        float scale=1.0f ;//scale factor
        float scaleSpeed=0.0f;
        float targetScale=1.0f;

        float origRad=0.0f;

        ColliderComponent* cc;
        SimpleSpriteComponent* ssc;

    public:

        ScaleComponent();
        ScaleComponent(float targetS,float scaleS);
        void init() override;
        void update(float dt) override;

        void setScale(float sc){scale=sc;
                                targetScale=sc;}

        void setGradulScale(float sc,float scaleS=5.0f){
            targetScale=sc;
            scaleSpeed=scaleS;
        }

};