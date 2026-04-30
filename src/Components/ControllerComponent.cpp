#include "Components/ControllerComponent.h"
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/SpellComponent.h"

ControllerComponent:: ControllerComponent(std::vector<SDL_Event>& keyPressedVec):keyPressedVec(keyPressedVec){}
void ControllerComponent::init(){
    tc = this->entity->getComponent<TransformComponent>();
}
void ControllerComponent::update(float dt){




    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    float logicalX = mouseX * (static_cast<float>(WIDTH) / WIN_WIDTH);
    float logicalY = mouseY * (static_cast<float>(HEIGHT) / WIN_HEIGHT);

    Vector2D mousePos={logicalX,logicalY};
    Vector2D playerPos = tc->getPos();
    Vector2D vectorPlayerMouse=(mousePos-playerPos);
    float speed=tc->getSpeed();
    float dist=vectorPlayerMouse.getMagnitude();


    if(dist <= 1.0f){// if the distance is so small the component just stop(stops the jittering)
        tc->setVel(Vector2D{0,0});
    }else{
        dir=vectorPlayerMouse*(1/dist);
        tc->setVel(dir*speed);
    }


    for(auto const &e : keyPressedVec){
        switch (e.key.keysym.scancode)
        {
            case SDL_SCANCODE_Z:
                
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::Bullet,dir);

                }
                
                    
                break;
            case SDL_SCANCODE_X:
                
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::Dash,dir);     
                }
                
                break;

            case SDL_SCANCODE_C:
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::Blast,dir);     
                }
                break;
            case SDL_SCANCODE_V:
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::IceAura,dir);     
                }
                break;
            case SDL_SCANCODE_B:
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::FireAura,dir);     
                }
                break;
            case SDL_SCANCODE_N:
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::ThunderAura,dir);     
                }
                break;
            case SDL_SCANCODE_A:
                if(auto* spell=this->entity->getComponent<SpellComponent>()){//we create a variable so we dont check twice
                    spell->castSpell(Spell::PiercingBullet,dir);     
                }
                break;
            default:
                break;
        }
    }

    keyPressedVec.clear(); //we clean the 

}