#pragma once

#include <iostream>

#include <managers/window_manager.hpp>
#include <managers/state_manager.hpp>
#include <managers/event_manager.hpp>
#include <managers/resource_manager.hpp>

class Application
{
public:
    Application();
    ~Application();

    // Wrapper for all application functions
    void run();

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
