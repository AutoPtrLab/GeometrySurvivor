#include "EntityManager.h"
#include "Components/ColliderComponent.h"
#include <algorithm>

EntityManager::EntityManager() {
    entityPool.reserve(100);
}

EntityManager::~EntityManager() = default;

/* Entity& EntityManager::addEntity(){

    auto e= std::make_unique<Entity>();
    auto& newEntity =*e;
    entityPool.emplace(newEntity.getID(),std::move (e));

    updateVec.push_back(&newEntity);

    return newEntity;

} */
Entity &EntityManager::addEntity(int depth) {

    auto e = std::make_unique<Entity>(depth);
    auto &newEntity = *e;
    entityPool.emplace(newEntity.getID(), std::move(e));

    updateVec.push_back(&newEntity);

    renderVec.push_back(&newEntity);
    std::stable_sort(renderVec.begin(), renderVec.end(), [](const auto &a, const auto &b) { // stable sort so it doesnt reorder if the have the same depth
        return (a->getDepth() > b->getDepth());                                             // most depth wins and is nearer the beginning
    });

    return newEntity;
}

void EntityManager::addBufferEntity(std::unique_ptr<Entity> e) {
    bufferVec.push_back(std::move(e));
}

Entity *EntityManager::getEntity(size_t ID) {

    auto it = entityPool.find(ID);
    if (it != entityPool.end()) {
        return it->second.get();
    } else {
        return nullptr;
    }
}

void EntityManager::deleteEntity(size_t ID) {

    auto it = entityPool.find(ID); // we make sure the ID exist
    if (it != entityPool.end()) {
        it->second->destroy();
    }
}

void EntityManager::garbageCollector() {

    updateVec.erase(std::remove_if(updateVec.begin(), updateVec.end(), [](Entity *e) { return !e->isActive(); }), updateVec.end());
    renderVec.erase(std::remove_if(renderVec.begin(), renderVec.end(), [](Entity *e) { return !e->isActive(); }), renderVec.end());

    for (auto it = entityPool.begin(); it != entityPool.end();) {
        if (!it->second->isActive()) {
            it = entityPool.erase(it);
        } else {
            ++it;
        }
    }
}
void EntityManager::update(float dt) {

    for (const auto &e : updateVec) {
        e->update(dt);
    }
    garbageCollector();
}

void EntityManager::render(SDL::RendererPtr r) {

    for (auto const &e : renderVec) {
        e->render(r);
    }
}

void EntityManager::flushBuffer() {
    if (bufferVec.empty()) {
        return;
    }

    for (auto &e : bufferVec) {

        updateVec.push_back(e.get());
        renderVec.push_back(e.get());
        entityPool.emplace(e->getID(), std::move(e));
    }

    std::stable_sort(renderVec.begin(), renderVec.end(), [](const auto &a, const auto &b) { // stable sort so it doesnt reorder if the have the same depth
        return (a->getDepth() > b->getDepth());                                             // most depth wins and is nearer the beginning
    });

    bufferVec.clear();
}
