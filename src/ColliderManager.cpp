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

        bool shouldCheck = (tag1 == ColliderFaction::Bullet && tag2 == ColliderFaction::Enemy) ||
                           (tag1 == ColliderFaction::Enemy && tag2 == ColliderFaction::Bullet) ||
                           (tag1 == ColliderFaction::Player && tag2 == ColliderFaction::Enemy);


        if (!shouldCheck) continue; // if they dont interact we skip the iteration

        if (colliderA->checkCollision(*colliderB)) {// if they collide
            printf("NIGGEr\n");
        }
    }
}
}