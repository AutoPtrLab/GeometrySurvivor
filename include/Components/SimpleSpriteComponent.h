#include "Component.h"
#include "Vector2D.h"

class TransformComponent;//forward declaration of the transformComponent



class SimpleSpriteComponent : public Component<SimpleSpriteComponent>{

    private:

        int radius =8; //lenght in pixels
        int sides=3;

        SDL::Color color={255,0,0,255};//color that we are currently rendering

        SDL::Color firstColor={255,0,0,255};
        SDL::Color secColor={255,0,0,120};
        SDL::Color hitColor={255, 255, 255, 220}; //white 

        TransformComponent *tc=nullptr;
        Vector2D prevPos;


    public:
        SimpleSpriteComponent();
        SimpleSpriteComponent(int radius,int sides,SDL::Color color=SDL::Colors::Red);//size of the geometry shape and what regular polygon is it
        void init() override;
        void render(SDL::RendererPtr r) override;
        void setFirstColor(){this->color=firstColor;}
        void setSecColor(){this->color=secColor;}
        void setHitColor(){this->color=hitColor;}
        

};