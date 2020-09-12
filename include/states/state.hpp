#pragma once

#include <managers/state_manager.hpp>
#include <sketches/array.hpp>
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
