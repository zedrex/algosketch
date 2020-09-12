#pragma once

#include <states/state.hpp>

class GraphSketchMenu : public State
{
public:
    GraphSketchMenu(StateManager *applicationStateManager, Action action);
    ~GraphSketchMenu();

    SketchContainer *getSketchContainer();
};