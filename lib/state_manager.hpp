#pragma once
#include <iostream>

#include <window_manager.hpp>
#include <event_manager.hpp>
#include <resource_manager.hpp>

class State;

enum class Action
{
    ChangeToMainMenu,
    ChangeToNewSketchMenu,
    ChangeToLoadSketchMenu,
    ChangeToOptionsMenu,
    QuitApplication,
    Array,
    Graph,
    Grid,
    String,
    Reset,
    Run,
    Pause,
    Back
};

class StateManager
{
public:
    StateManager();
    StateManager(WindowManager *applicationWindowManager, EventManager *applicationEventManager, ResourceManager *applicationResourceManager);
    ~StateManager();

    void setWindowManager(WindowManager *applicationWindowManager);
    void setEventManager(EventManager *applicationEventManager);
    void setResourceManager(ResourceManager *applicationResourceManager);

    void start();

    State *getCurrentState();

    WindowManager *getApplicationWindow();

    EventManager *getEventManager();

    void perform(Action action);

    void changeState(State *newState);

    void update();

    void render();

private:
    WindowManager *windowManager;
    EventManager *eventManager;
    ResourceManager *resourceManager;

    State *currentState;
};
