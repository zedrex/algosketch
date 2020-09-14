#pragma once

#include <states/state.hpp>

class CreditsMenu : public State
{
public:
    CreditsMenu(StateManager *applicationStateManager);
    ~CreditsMenu();
};