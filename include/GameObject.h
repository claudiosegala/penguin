#pragma once

#include <Component.h>
#include <Logger.h>
#include <Rect.h>
#include <Vec2.h>
#include <Util.h>

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Component;

class GameObject {
    public:

        Rect box;

        float angle;

        GameObject();

        ~GameObject();

        void Start();

        void Update(float);

        void Render();

        bool IsDead();

        void RequestDelete();

        void AddComponent(Component*);

        void RemoveComponent(std::shared_ptr<Component>&);

        std::shared_ptr<Component> GetComponent(std::string);

        std::shared_ptr<Component> GetPenguinBody();

        std::shared_ptr<Component> GetPenguinCannon();

        std::shared_ptr<Component> GetBullet();

        std::shared_ptr<Component> GetAlien();

        void NotifyCollision(GameObject&);

    private:

        bool started;

        bool isDead;

        std::vector<std::shared_ptr<Component>> components;
};