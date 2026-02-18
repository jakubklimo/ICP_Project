#pragma once

#include <vector>

#include "object.hpp"

class Object;

class World {
    public:
        void addObject(Object* obj);
        const std::vector<Object*>& getObjects() const;

    private:
        std::vector<Object*> objects;
};