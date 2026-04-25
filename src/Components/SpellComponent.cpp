#include "Components/SpellComponent.h"

SpellComponent::SpellComponent(){

}

SpellComponent::~SpellComponent()=default;


void SpellComponent::addSpell(SpellType type,std::function<void(Vector2D pos,Vector2D dir)> spell){ //doesnt let you overWrite Spells for know

    spells.emplace(type,spell);

}

void SpellComponent::castSpell(SpellType type,Vector2D initPos,Vector2D dir){
    auto it =spells.find(type);
    if(it != spells.end()){
        it->second(initPos,dir);
    }

}