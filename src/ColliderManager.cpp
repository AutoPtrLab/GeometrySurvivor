#include "ColliderManager.h"
#include "Components/ComponentsList.h"
#include "Entity.h"
ColliderManager::ColliderManager(const std::vector<Entity *> &updateVec) : updateVec(updateVec) {}

ColliderManager::~ColliderManager() = default;

void ColliderManager::update() {
    this->checkCollisions();
}

void ColliderManager::checkCollisions() {
    for (int i = 0; i < updateVec.size(); i++) {
        if (!updateVec[i])
            continue;
        auto colliderA = updateVec[i]->getComponent<ColliderComponent>();
        if (!colliderA)
            continue;

        for (int j = i + 1; j < updateVec.size(); j++) {
            if (!updateVec[j])
                continue;
            auto colliderB = updateVec[j]->getComponent<ColliderComponent>();
            if (!colliderB)
                continue;

            if (!colliderA->checkCollision(*colliderB))
                continue;

            if (colliderB->getLayer() & colliderA->getMask()) {
                colliderA->onCollision(colliderB->getEntity());
            }

            if (colliderA->getLayer() & colliderB->getMask()) {
                colliderB->onCollision(colliderA->getEntity());
            }
        }
    }
}
