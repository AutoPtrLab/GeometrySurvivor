#include "Components/SimpleSpriteComponent.h"
#include "SDL_wrapper.h"
#include "Entity.h"
#include "Components/TransformComponent.h"
#include <cmath>

void SimpleSpriteComponent::init(){
    tc=entity->getComponent<TransformComponent>();
    
}
void SimpleSpriteComponent::update(float dt){

}
void SimpleSpriteComponent::render(SDL::RendererPtr r){

    float half = (side)/ 2.0f;
    
    float x = tc->getPos().x - half;
    float y = tc->getPos().y - half;
    float s = static_cast<float>(side);

    SDL_SetRenderDrawColor(r, 255, 0, 0, 155); // tranparency
    SDL_FRect rect = { x, y, s, s };
    SDL_RenderFillRectF(r, &rect);

    SDL_SetRenderDrawColor(r, 255, 0, 0, 255); // RGBA Testing
    SDL_RenderDrawLineF(r, x,     y,     x + s, y    ); // top
    SDL_RenderDrawLineF(r, x + s, y,     x + s, y + s); // right
    SDL_RenderDrawLineF(r, x + s, y + s, x,     y + s); // bottom
    SDL_RenderDrawLineF(r, x,     y + s, x,     y    ); // left

}