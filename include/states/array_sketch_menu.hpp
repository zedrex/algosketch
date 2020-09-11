#pragma once
#include<states/state.hpp>

class ArraySketchMenu : public State
{
public:
    ArraySketchMenu(StateManager *applicationStateManager);
    ~ArraySketchMenu();

    SketchContainer *getSketchContainer();
};