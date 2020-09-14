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
    this->leftButtonHeld = false;

    this->rightButtonPressed = false;
    this->rightButtonReleased = false;
    this->rightButtonHeld = false;

    this->lastKey = "";
}
EventManager::~EventManager() {}

void EventManager::update()
{
    float timeSinceLastInput = this->inputClock.getElapsedTime().asSeconds();

    this->leftButtonPressed = false;
    this->leftButtonReleased = false;
    this->rightButtonPressed = false;
    this->rightButtonReleased = false;

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
                {
                    this->leftButtonPressed = true;
                    this->leftButtonHeld = true;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    this->rightButtonPressed = true;
                    this->rightButtonHeld = true;
                }
            }

            // Mouse Button Released
            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    this->leftButtonReleased = true;
                    this->leftButtonHeld = false;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    this->rightButtonReleased = true;
                    this->rightButtonHeld = false;
                }
            }

            // Printable Key
            if (event.type == sf::Event::TextEntered)
            {
                this->lastKey = char(event.text.unicode);
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                if (event.mouseWheel.delta > 0)
                {
                    this->stateManager->getApplicationWindow()->changeFPS(5);
                }

                else if (event.mouseWheel.delta < 0)
                {
                    this->stateManager->getApplicationWindow()->changeFPS(-5);
                }
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

bool EventManager::isLeftKeyHeld()
{
    return this->leftButtonHeld;
}

bool EventManager::isRightKeyPressed()
{
    return this->rightButtonPressed;
}

bool EventManager::isRightKeyReleased()
{
    return this->rightButtonReleased;
}

bool EventManager::isRightKeyHeld()
{
    return this->rightButtonHeld;
}

std::string EventManager::getCurrentKey()
{
    return this->lastKey;
}