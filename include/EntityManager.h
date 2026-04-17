#include "Entity.h"
#include <unordered_map>


class EntityManager{
    private:

        std::unordered_map<size_t,std::unique_ptr<Entity>> entityPool; //hash map of the entities with their own ID

        std::vector<Entity*> updateVec;//observer of all entities
        std::vector<Entity*> renderVec;//Vector that host all the drawable entities

    public:

        EntityManager();
        ~EntityManager();

        Entity& addEntity(int depth);
        Entity& addEntity();

        Entity* getEntity();

        void deleteEntity(size_t ID); 
        void garbageCollector();

        void update(float dt);
        void render();
};