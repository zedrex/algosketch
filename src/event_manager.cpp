#include <event_manager.hpp>
#include <state_manager.hpp>

EventManager::EventManager() {}
EventManager::~EventManager() {}

sf::Vector2i EventManager::getMousePosition()
{
    return sf::Mouse::getPosition(*(this->stateManager->getApplicationWindow()->getRenderWindow()));
}