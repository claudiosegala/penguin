#include <Bullet.h>
#include <GameObject.h>
#include <Vec2.h>
#include <Sprite.h>
#include <Collider.h>
#include <PenguinBody.h>

Bullet::Bullet(GameObject& go, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime) : Component(go) {
    auto bg = new Sprite(go, sprite, frameCount, frameTime);
    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);

    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = Vec2(1, 0).GetRotate(angle) * speed;
}

void Bullet::Update(float dt) {
    auto diff = this->speed * dt;

    this->distanceLeft -= diff.GetLength();

    if (this->distanceLeft <= 0) {
        this->associated.RequestDelete();
        return;
    }

    this->associated.box.vector -= diff;
}

void Bullet::Render() {}

void Bullet::NotifyCollision(GameObject &other) {
    auto component = other.GetComponent("PenguinBody");

    if (component != nullptr) {
        auto penguin = std::static_pointer_cast<PenguinBody>(component);
        this->associated.RequestDelete();
    }
}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage() {
    return this->damage;
}