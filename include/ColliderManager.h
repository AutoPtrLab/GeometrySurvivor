#pragma once
#include <vector>

class Entity;//forward declaration

class ColliderManager {

    private:

        const std::vector<Entity*> &updateVec ; //references to the updateVec in the entityManage
        
        void checkCollisions();

    public:

        ColliderManager( const std::vector<Entity*> &updateVec);
        ~ColliderManager();

        void update();


};