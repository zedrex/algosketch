#pragma once

#include <states/state.hpp>

class GridSketchMenu : public State
{
public:
    GridSketchMenu(StateManager *applicationStateManager, Action action);
    ~GridSketchMenu();

    SketchContainer *getSketchContainer();
};