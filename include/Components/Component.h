#pragma once
#include <cstddef>
#include "SDL_wrapper.h"


enum class Faction{ None,Enemy,Player,Bullet,Spell};//faction of each entity

using ComponentID = std::size_t; //alias for Component ID

inline ComponentID getUniqueComponentID() { //generator of ComponentIDs
    static ComponentID lastID = 0;
    return lastID++;
}

//we need to implement a baseclass that is not a template to implement our containers in entity and use de CRTP
class BaseComponent{

    public:
        virtual ~BaseComponent()=default;
        virtual void  update(float dt){};
        virtual void render(SDL::RendererPtr r){}//NOT obligatory for every component, we dont use the alias here so we dont include "SDL_wrapper"
        virtual void init(){}//Use to aquire the components that your component needs
        virtual ComponentID getID() const = 0 ;
};


class Entity;//forward declaration of entity

template <typename T>//CRTP
class Component:public BaseComponent{

    friend class Entity;

    protected:
        Entity* entity;//pointer to its own entity
    public: 
        
        
        static ComponentID getStaticID() { //compile time call
            static ComponentID ID=getUniqueComponentID();
            return ID;
        }

        ComponentID getID() const override { // virtual call when we dont know the type
            return getStaticID();
        }

};

