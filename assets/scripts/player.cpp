#include <iostream>

class Player {
public:
    Player(const std::string& name, int health)
        : name(name), health(health), x(0), y(0) {}

    void move(int dx, int dy) {
        x += dx;
        y += dy;
        std::cout << "Player " << name << " moved to (" << x << ", " << y << ")\n";
    }

    void takeDamage(int damage) {
        health -= damage;
        std::cout << "Player " << name << " took " << damage << " damage. Health: " << health << "\n";
    }

private:
    std::string name;
    int health;
    int x, y;
};

int main() {
    Player player("Hero", 100);
    player.move(10, 5);
    player.takeDamage(20);
    
    return 0;
}