#include "Components/SpellComponent.h"

SpellComponent::SpellComponent(){

}

SpellComponent::~SpellComponent()=default;


void SpellComponent::addSpell(Spell::SpellType type,std::unique_ptr<ISpell> ptr){ 

    spells[type]=std::move(ptr);

}

void SpellComponent::castSpell(Spell::SpellType type,Vector2D dir){
               
    if( auto& spell=spells[type] ){
        spell->cast(*this->entity,dir);
    }

}


void SpellComponent::update(float dt){

    for (auto& s:spells){
        if(!s) continue;
        s->update(*this->entity,dt);
    }

}


void SpellComponent::render(SDL::RendererPtr r){

    for (auto& s:spells){
        if(!s) continue;
        s->render(*this->entity,r);
    }
}