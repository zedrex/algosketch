#pragma once

#include <managers/state_manager.hpp>
#include <sketch_array.hpp>
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

    SketchContainer *getSketchContainer();

protected:
    std::vector<StateElement *> stateElementList;
    StateManager *stateManager;
    SketchContainer *sketchContainer;
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

    SketchContainer *getSketchContainer();
};
