#include <state_elements/state_element.hpp>

class SketchContainer : public StateElement
{
public:
    SketchContainer(StateManager *applicationStateManager, float x, float y, float width, float height, ActionParameter parameter);
    ~SketchContainer();

    bool isPaused();
    void setPaused(bool signal);
    virtual void reset() = 0;

protected:
    bool paused;
    ActionParameter algorithmType;
};