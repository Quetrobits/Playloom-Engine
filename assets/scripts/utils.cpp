#include <iostream>
#include <cmath>

class Vector2D {
public:
    float x, y;

    Vector2D(float x, float y) : x(x), y(y) {}

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    static Vector2D add(const Vector2D& v1, const Vector2D& v2) {
        return Vector2D(v1.x + v2.x, v1.y + v2.y);
    }
};

int main() {
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);

    std::cout << "Length of v1: " << v1.length() << "\n";
    Vector2D v3 = Vector2D::add(v1, v2);
    std::cout << "v1 + v2 = (" << v3.x << ", " << v3.y << ")\n";
    
    return 0;
}