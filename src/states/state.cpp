#include <managers/state_manager.hpp>
#include <states/state.hpp>
#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>

State::State(StateManager *applicationStateManager)
{
    this->stateManager = applicationStateManager;
}

State::~State()
{
}

void State::render()
{
    for (auto stateElement : stateElementList)
    {
        for (auto drawable : *((*stateElement).getDrawableList()))
            stateManager->getApplicationWindow()->render(*drawable);

        for (auto drawable : *((*stateElement).getTemporaryDrawableList()))
            stateManager->getApplicationWindow()->render(*drawable);
    }
}

void State::update()
{
    for (auto stateElement : stateElementList)
    {
        stateElement->update();
    }
}

SketchContainer *State::getSketchContainer()
{
    return sketchContainer;
}

TextForm *State::getTextForm()
{
    return stateTextForm;
}