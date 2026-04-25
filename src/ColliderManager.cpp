#include "ColliderManager.h"
#include "Entity.h"
#include "Components/ComponentsList.h"
ColliderManager::ColliderManager(const std::vector<Entity*> &updateVec):updateVec(updateVec){

}

ColliderManager::~ColliderManager() =default;

void ColliderManager::update(){
    this->checkCollisions();
}       

void ColliderManager::checkCollisions() {
    for (int i = 0; i < updateVec.size(); i++) {
        if (!updateVec[i]) continue;
        auto colliderA = updateVec[i]->getComponent<ColliderComponent>();
        if (!colliderA) continue;

        for (int j = i + 1; j < updateVec.size(); j++) {
            if (!updateVec[j]) continue;
            auto colliderB = updateVec[j]->getComponent<ColliderComponent>();
            if (!colliderB) continue;

            auto tag1 = colliderA->getFaction();
            auto tag2 = colliderB->getFaction();

            bool shouldCheck = (tag1 == Faction::Bullet && tag2 == Faction::Enemy) ||
                               (tag1 == Faction::Enemy  && tag2 == Faction::Bullet) ||
                               (tag1 == Faction::Player && tag2 == Faction::Enemy)  ||
                               (tag1 == Faction::Enemy  && tag2 == Faction::Player);

            if (!shouldCheck) continue;
            if (!colliderA->checkCollision(*colliderB)) continue;

            // Normalizamos quién es quién
            Entity* bullet = nullptr;
            Entity* enemy  = nullptr;
            Entity* player = nullptr;

            if      (tag1 == Faction::Bullet && tag2 == Faction::Enemy)  { bullet = updateVec[i]; enemy  = updateVec[j]; }
            else if (tag1 == Faction::Enemy  && tag2 == Faction::Bullet) { bullet = updateVec[j]; enemy  = updateVec[i]; }
            else if (tag1 == Faction::Player && tag2 == Faction::Enemy)  { player = updateVec[i]; enemy  = updateVec[j]; }
            else if (tag1 == Faction::Enemy  && tag2 == Faction::Player) { player = updateVec[j]; enemy  = updateVec[i]; }

            if (bullet && enemy) {
                bullet->destroy();
                enemy->destroy();
                if (auto* hp = enemy->getComponent<HealthComponent>())
                    hp->getHit(20);
            }

            if (player && enemy) {
                if (auto* hp = player->getComponent<HealthComponent>())
                    hp->getHit(10);
            }
        }
    }
}