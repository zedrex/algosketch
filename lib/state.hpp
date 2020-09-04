#pragma once

#include <state_manager.hpp>
#include <vector>

class StateElement;
// Abstract class for application states
class State
{
public:
    State(StateManager *applicationStateManager);
    ~State();

    void render();

    void update();

protected:
    std::vector<StateElement *> stateElementList;
    StateManager *stateManager;
};

// Main menu state
class MainMenu : public State
{
public:
    MainMenu(StateManager *applicationStateManager);
    ~MainMenu();
};

class NewSketchMenu : public State
{
public:
    NewSketchMenu(StateManager *applicationStateManager);
    ~NewSketchMenu();
};

class ArraySketchMenu : public State
{
public:
    ArraySketchMenu(StateManager *applicationStateManager);
    ~ArraySketchMenu();
};