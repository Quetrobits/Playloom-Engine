#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <cassert>
#include <algorithm>

struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2 Normalized() const {
        float mag = Magnitude();
        assert(mag != 0 && "Cannot normalize a zero vector");
        return Vector2(x / mag, y / mag);
    }

    float Dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }
};

struct Rigidbody {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float mass;

    Rigidbody(Vector2 pos, float m) : position(pos), mass(m) {
        velocity = Vector2();
        acceleration = Vector2();
    }

    void ApplyForce(const Vector2& force) {
        acceleration += force * (1.0f / mass);
    }

    void Update(float deltaTime) {
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
        acceleration = Vector2(); // Reset acceleration for the next frame
    }
};

class Collider {
public:
    virtual bool IsColliding(const Collider& other) const = 0;
    virtual ~Collider() = default;
};

class CircleCollider : public Collider {
public:
    Vector2 center;
    float radius;

    CircleCollider(Vector2 c, float r) : center(c), radius(r) {}

    bool IsColliding(const Collider& other) const override {
        const CircleCollider* circle = dynamic_cast<const CircleCollider*>(&other);
        if (circle) {
            float distance = (center - circle->center).Magnitude();
            return distance < (radius + circle->radius);
        }
        return false;
    }
};

class AABBCollider : public Collider {
public:
    Vector2 min;
    Vector2 max;

    AABBCollider(Vector2 min, Vector2 max) : min(min), max(max) {}

    bool IsColliding(const Collider& other) const override {
        const AABBCollider* aabb = dynamic_cast<const AABBCollider*>(&other);
        if (aabb) {
            return (min.x < aabb->max.x && max.x > aabb->min.x &&
                    min.y < aabb->max.y && max.y > aabb->min.y);
        }
        return false;
    }
};

class PhysicsObject {
public:
    std::shared_ptr<Rigidbody> rigidbody;
    std::shared_ptr<Collider> collider;

    PhysicsObject(std::shared_ptr<Rigidbody> rb, std::shared_ptr<Collider> col)
        : rigidbody(rb), collider(col) {}

    void Update(float deltaTime) {
        if (rigidbody) {
            rigidbody->Update(deltaTime);
        }
    }

    void Render() const {
        std::cout << "PhysicsObject at position (" << rigidbody->position.x
                  << ", " << rigidbody->position.y << ")\n";
    }
};

class PhysicsWorld {
public:
    void AddObject(const std::shared_ptr<PhysicsObject>& object) {
        objects.push_back(object);
    }

    void RemoveObject(const std::shared_ptr<PhysicsObject>& object) {
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

    void Update(float deltaTime) {
        for (auto& object : objects) {
            object->Update(deltaTime);
        }

        // Simple collision detection
        for (size_t i = 0; i < objects.size(); ++i) {
            for (size_t j = i + 1; j < objects.size(); ++j) {
                if (objects[i]->collider && objects[j]->collider) {
                    if (objects[i]->collider->IsColliding(*objects[j]->collider)) {
                        HandleCollision(objects[i], objects[j]);
                    }
                }
            }
        }
    }

    void Render() const {
        for (const auto& object : objects) {
            object->Render();
        }
    }

private:
    std::vector<std::shared_ptr<PhysicsObject>> objects;

    void HandleCollision(const std::shared_ptr<PhysicsObject>& a, const std::shared_ptr<PhysicsObject>& b) {
        std::cout << "Collision detected!\n";
        Vector2 normal = (b->rigidbody->position - a->rigidbody->position).Normalized();
        a->rigidbody->ApplyForce(-normal * 10.0f);
        b->rigidbody->ApplyForce(normal * 10.0f);
    }
};

int main() {
    PhysicsWorld world;

    auto obj1 = std::make_shared<PhysicsObject>(
        std::make_shared<Rigidbody>(Vector2(0, 0), 1.0f),
        std::make_shared<CircleCollider>(Vector2(0, 0), 1.0f)
    );

    auto obj2 = std::make_shared<PhysicsObject>(
        std::make_shared<Rigidbody>(Vector2(3, 0), 1.0f),
        std::make_shared<CircleCollider>(Vector2(3, 0), 1.0f)
    );

    auto obj3 = std::make_shared<PhysicsObject>(
        std::make_shared<Rigidbody>(Vector2(5, 5), 2.0f),
        std::make_shared<AABBCollider>(Vector2(4, 4), Vector2(6, 6))
    );

    world.AddObject(obj1);
    world.AddObject(obj2);
    world.AddObject(obj3);

    const float deltaTime = 0.016f; // Assuming 60 FPS

    for (int i = 0; i < 60; ++i) {
        obj1->rigidbody->ApplyForce(Vector2(0.5f, 0));
        obj2->rigidbody->ApplyForce(Vector2(-0.3f, 0));
        world.Update(deltaTime);
        world.Render();
    }

    return 0;
}