#pragma once
#include<states/state.hpp>

class MainMenu : public State
{
public:
    MainMenu(StateManager *applicationStateManager);
    ~MainMenu();
};