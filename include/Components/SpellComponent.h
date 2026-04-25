#pragma once
#include "Component.h"
#include "unordered_map"
#include "functional"
#include "Vector2D.h"

enum class SpellType{
    Bullet,
    Dash
};


class SpellComponent : public Component<SpellComponent>{

    private:

        std::unordered_map<SpellType,std::function <void (Vector2D pos,Vector2D dir)>> spells;

    public:

        SpellComponent();
        ~SpellComponent();

        void addSpell(SpellType type,std::function<void(Vector2D pos,Vector2D dir)> spell); //you cant overwrite spells
        void castSpell(SpellType type,Vector2D initPos,Vector2D dir);//if thre is no 


};