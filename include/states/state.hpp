#pragma once

#include <managers/state_manager.hpp>
#include <sketches/sketch_container.hpp>
#include <state_elements/text_form.hpp>
#include <vector>

class StateElement;

// Mother class for application states
class State
{
public:
    State(StateManager *applicationStateManager);
    ~State();

    void render();

    void update();

    void addStateElement(StateElement *newElement);
    SketchContainer *getSketchContainer();
    TextForm *getTextForm();

protected:
    std::vector<StateElement *> stateElementList;
    StateManager *stateManager;
    SketchContainer *sketchContainer;
    TextForm *stateTextForm;
};
