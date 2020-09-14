#pragma once

#include <states/state.hpp>

class HelpMenu : public State
{
public:
    HelpMenu(StateManager *applicationStateManager);
    ~HelpMenu();
};