#include <iostream>
#include <functional>
#include <vector>

class EventHandler {
public:
    void addEventListener(const std::string& event, std::function<void()> listener) {
        eventListeners[event].push_back(listener);
    }

    void dispatchEvent(const std::string& event) {
        if (eventListeners.find(event) != eventListeners.end()) {
            for (auto& listener : eventListeners[event]) {
                listener();
            }
        }
    }

private:
    std::unordered_map<std::string, std::vector<std::function<void()>>> eventListeners;
};

int main() {
    EventHandler eventHandler;

    // Register events
    eventHandler.addEventListener("player_death", []() {
        std::cout << "Player has died!" << std::endl;
    });

    // Dispatch events
    eventHandler.dispatchEvent("player_death");

    return 0;
}