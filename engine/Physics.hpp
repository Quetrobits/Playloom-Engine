#ifndef PHYSICS_HPP
#define PHYSICS_HPP

class Physics {
public:
    Physics();
    ~Physics();

    void update(float deltaTime);
    void applyForce(float forceX, float forceY);
    void detectCollisions();

private:
    float gravity;
};

#endif // PHYSICS_HPP