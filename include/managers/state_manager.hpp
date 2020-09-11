#pragma once
#include <iostream>

#include <managers/window_manager.hpp>
#include <managers/event_manager.hpp>
#include <managers/resource_manager.hpp>

class State;

enum class ActionType
{
    ChangeToMainMenu,
    ChangeToNewSketchMenu,
    ChangeToLoadSketchMenu,
    ChangeToOptionsMenu,
    QuitApplication,
    ChangeToArrayMenu,
    ChangeToArrayAlgorithmMenu,
    ChangeToGraphMenu,
    ChangeToGraphAlgorithmMenu,
    Grid,
    String,
    Reset,
    Run,
    Pause,
    Back
};

enum class ActionParameter
{
    InsertionSort,
    SelectionSort,
    BubbleSort,
    DepthFirstSearch,
    BreadthFirstSearch,
    DijkstraAlgorithm,
    Null
};

using Action = std::pair<ActionType, ActionParameter>;

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
