#include <iostream>

class HealthComponent {
public:
    HealthComponent(int maxHealth) : maxHealth(maxHealth), currentHealth(maxHealth) {}

    void takeDamage(int damage) {
        currentHealth -= damage;
        if (currentHealth < 0) currentHealth = 0;
        std::cout << "Health: " << currentHealth << "/" << maxHealth << "\n";
    }

    void heal(int amount) {
        currentHealth += amount;
        if (currentHealth > maxHealth) currentHealth = maxHealth;
        std::cout << "Health: " << currentHealth << "/" << maxHealth << "\n";
    }

private:
    int maxHealth;
    int currentHealth;
};

// Example usage
int main() {
    HealthComponent health(100);
    health.takeDamage(30);
    health.heal(20);
    
    return 0;
}