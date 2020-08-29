#pragma once

#include <SFML/Graphics.hpp>

// Forward declaration of StateManager
class StateManager;

class EventManager
{
public:
    EventManager();
    ~EventManager();

    sf::Vector2i getMousePosition();

private:
    StateManager *stateManager;
};