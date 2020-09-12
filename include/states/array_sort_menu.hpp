#pragma once
#include<states/state.hpp>

class ArraySortMenu: public State{
    public:
    ArraySortMenu(StateManager *applicationStateManager);
    ~ArraySortMenu();
};