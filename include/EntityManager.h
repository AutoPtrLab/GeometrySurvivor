#include "Entity.h"
#include <unordered_map>


class EntityManager{
    private:

        std::unordered_map<size_t,std::unique_ptr<Entity>> entityPool; //hash map of the entities with their own ID

        std::vector<std::unique_ptr<Entity>> bufferVec;//this vector holds the newly created entities so that they dont collide in the update() vec mid update 
        std::vector<Entity*> updateVec;//observer of all entities
        std::vector<Entity*> renderVec;//Vector that host all the drawable entities

     

    public:

        EntityManager();
        ~EntityManager();

        Entity& addEntity(int depth); //this functions only work before the start of the main loop
      //  Entity& addEntity();

        void addBufferEntity(std::unique_ptr<Entity> e);//call for an already build-up entity from the factory
        

        Entity* getEntity(size_t ID);

        void deleteEntity(size_t ID); 
        void garbageCollector();

        void update(float dt);
        void render(SDL::RendererPtr r);
        void flushBuffer();//inyects the queued entitites

        
        
        const std::vector<Entity*>& getUpdateVec(){return updateVec;}
};