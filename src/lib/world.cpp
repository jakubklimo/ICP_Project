#include "world.hpp"

void World::addObject(Object* obj) {
    objects.push_back(obj);
}

const std::vector<Object*>& World::getObjects() const {
    return objects;
}