#pragma once

#include <iostream>

#include <managers/window_manager.hpp>
#include <managers/event_manager.hpp>
#include <managers/resource_manager.hpp>

class State;

enum class Action
{
    ChangeToMainMenu,
    ChangeToNewSketchMenu,
    ChangeToLoadSketchMenu,
    ChangeToOptionsMenu,
    ChangeToCreditsMenu,
    QuitApplication,
    Array,
    Graph,
    Grid,
    String,
    Create,
    Reset,
    Run,
    Pause,
    Back,
    BubbleSort,
    SelectionSort,
    InsertionSort,
    ShellSort,
    GnomeSort,
    GraphDepthFirstSearch,
    GraphBreadthFirstSearch,
    GraphDijkstra,
    GridDepthFirstSearch,
    GridBreadthFirstSearch,
    GridAStarPathfinder
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
