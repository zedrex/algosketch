#pragma once

#include <state_elements/state_element.hpp>

class SketchContainer : public StateElement
{
public:
    SketchContainer(StateManager *applicationStateManager, float x, float y, float width, float height);
    ~SketchContainer();

    bool isPaused();
    void setPaused(bool signal);
    virtual void create() = 0;
    virtual void reset() = 0;
    virtual void update() = 0;

protected:
    bool paused;
};