#pragma once

#include <SFML/Graphics.hpp>

// Forward declaration of StateManager
class StateManager;

class EventManager
{
public:
    EventManager(StateManager *applicationStateManager);
    ~EventManager();

    void update();

    sf::Vector2i getMousePosition();
    bool isLeftKeyPressed();
    bool isLeftKeyReleased();
    std::string getCurrentKey();

private:
    StateManager *stateManager;
    std::string lastKey;
    bool leftButtonPressed;
    bool leftButtonReleased;
    sf::Clock inputClock;
};