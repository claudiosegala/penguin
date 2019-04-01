#pragma once

#include <Component.h>
#include <Rectangle.h>
#include <Vector.h>
#include <Point.h>
#include <vector>
#include <string>
#include <memory>

namespace penguin {

    class GameObject {
        public:

        Rectangle box;

        GameObject();

        GameObject(Vector&, int, int);

        ~GameObject();

        void Update(float);

        void Render();

        bool IsDead();

        void RequestDelete();

        void AddComponent(Component*);

        void RemoveComponent(std::unique_ptr<Component>);

        std::unique_ptr<Component> GetComponent(std::string);

        private:

        bool isDead;

        std::vector<unique_ptr<Component>> components;
    };

}