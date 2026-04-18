#include "Component.h"
#include "Vector2D.h"

class TransformComponent;//forward declaration of the transformComponent

class SimpleSpriteComponent : public Component<SimpleSpriteComponent>{

    private:

        int side =8; //lenght in pixels
        TransformComponent *tc=nullptr;
        Vector2D prevPos;


    public:
        void init() override;
        void update(float dt) override;
        void render(SDL::RendererPtr r) override;

};