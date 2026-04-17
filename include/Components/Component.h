#pragma once
#include <cstddef>

using ComponentID = std::size_t; //alias for Component ID

inline ComponentID getUniqueComponentID() { //generator of ComponentIDs
    static ComponentID lastID = 0;
    return lastID++;
}

//we need to implement a baseclass that is not a template to implement our containers in entity and use de CRTP
class BaseComponent{

    public:
        virtual ~BaseComponent()=default;
        virtual void  update(float dt)=0;
        virtual void render(){}//NOT obligatory for every component
        virtual void init(){}//Use to aquire the components that your component needs
        virtual ComponentID getID() const = 0 ;
};


class Entity;//forward declaration of entity

template <typename T>//CRTP
class Component:public BaseComponent{

    friend class Entity;
    private:
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

