#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <window_manager.hpp>
#include <state_manager.hpp>
#include <event_manager.hpp>
#include <resource_manager.hpp>

class Application
{
public:
    Application();
    ~Application();

    // Wrapper for all application functions
    void run();

    void handleInput();

    // Update for the current tick
    void update();

    // Render for member window class
    void render();

private:
    WindowManager windowManager;
    StateManager stateManager;
    EventManager eventManager;
    ResourceManager resourceManager;
};
