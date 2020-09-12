#include <managers/event_manager.hpp>
#include <managers/state_manager.hpp>

// DEBUG
#include <iostream>

float EventManager::inputDelay = 0.01;

EventManager::EventManager(StateManager *applicationStateManager)
{
    this->stateManager = applicationStateManager;

    this->leftButtonPressed = false;
    this->leftButtonReleased = false;
    this->lastKey = "";
}
EventManager::~EventManager() {}

void EventManager::update()
{
    float timeSinceLastInput = this->inputClock.getElapsedTime().asSeconds();

    this->leftButtonPressed = false;
    this->leftButtonReleased = false;
    this->lastKey = "";

    sf::Event event;

    while (stateManager->getApplicationWindow()->getRenderWindow()->pollEvent(event))
    {
        if (timeSinceLastInput >= inputDelay)
        {
            this->inputClock.restart();

            if (event.type == sf::Event::Closed)
            {
                this->stateManager->getApplicationWindow()->terminateWindow();
            }

            // Mouse Button Pressed
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    this->leftButtonPressed = true;
            }

            // Mouse Button Released
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    this->leftButtonReleased = true;
            }

            // Printable Key
            if (event.type == sf::Event::TextEntered)
            {
                this->lastKey = char(event.text.unicode);
            }
        }
    }
}

sf::Vector2i EventManager::getMousePosition()
{
    return sf::Mouse::getPosition(*(this->stateManager->getApplicationWindow()->getRenderWindow()));
}

bool EventManager::isLeftKeyPressed()
{
    return this->leftButtonPressed;
}

bool EventManager::isLeftKeyReleased()
{
    return this->leftButtonReleased;
}

std::string EventManager::getCurrentKey()
{
    return this->lastKey;
}