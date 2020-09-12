#pragma once

#include <states/state.hpp>

class NewSketchMenu : public State
{
public:
    NewSketchMenu(StateManager *applicationStateManager);
    ~NewSketchMenu();
};