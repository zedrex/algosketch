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
        if (event.type == sf::Event::Closed)
        {
            this->stateManager->getApplicationWindow()->terminateWindow();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
                this->lastKey = "ENTER";
            else if (event.key.code == sf::Keyboard::Backspace)
                this->lastKey = "BACKSPACE";
        }
        else if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode < 0x80)
                this->lastKey = char(event.text.unicode);
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