#include "ColliderManager.h"
#include "Entity.h"
#include "Components/ComponentsList.h"
ColliderManager::ColliderManager(const std::vector<Entity*> &updateVec):updateVec(updateVec){

}

ColliderManager::~ColliderManager() =default;

void ColliderManager::update(){
    this->checkCollisions();
}       

void ColliderManager::checkCollisions(){
    for (int i = 0; i < updateVec.size(); i++) {
        if (!updateVec[i]) continue;
        auto colliderA = updateVec[i]->getComponent<ColliderComponent>();
        if (!colliderA) continue;

        for (int j = i + 1; j < updateVec.size(); j++) { //j=i+1 so we dont double check entities
            if (!updateVec[j]) continue; 
            auto colliderB = updateVec[j]->getComponent<ColliderComponent>();
            if (!colliderB) continue;

            auto tag1=colliderA->getFaction();
            auto tag2 = colliderB->getFaction();

            bool shouldCheck = (tag1 == Faction::Bullet && tag2 == Faction::Enemy) ||
                            (tag1 == Faction::Enemy && tag2 == Faction::Bullet) ||
                            (tag1 == Faction::Player && tag2 == Faction::Enemy);


            if (!shouldCheck) continue; // if they dont interact we skip the iteration

            if (colliderA->checkCollision(*colliderB)) {// if they collide
                if(colliderA->getFaction() == Faction::Player && colliderB->getFaction()==Faction::Enemy){
                    updateVec[i]->getComponent<HealthComponent>()->getHit(10);
                }
            }
        }
    }
}