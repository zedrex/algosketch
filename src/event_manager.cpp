#include <event_manager.hpp>
#include <state_manager.hpp>

// DEBUG
#include <iostream>

EventManager::EventManager(StateManager *applicationStateManager) { this->stateManager = applicationStateManager; }
EventManager::~EventManager() {}

void EventManager::update()
{
    sf::Event event;
    this->lastKey = "";
    while (stateManager->getApplicationWindow()->getRenderWindow()->pollEvent(event))
    {
        if (event.type == sf::Event::TextEntered)
        {
            //  this->lastKey += std::to_string(char(event.text.unicode));
            std::cout << event.text.unicode << std::endl;
        }
    }
}

sf::Vector2i EventManager::getMousePosition()
{
    return sf::Mouse::getPosition(*(this->stateManager->getApplicationWindow()->getRenderWindow()));
}

std::string EventManager::getCurrentKey()
{
    return this->lastKey;
}