#include <sketches/array.hpp>
#include <states/state.hpp>

SketchContainer::SketchContainer(StateManager *applicationStateManager, float x, float y, float width, float height)
    : StateElement(applicationStateManager, x, y, width, height)
{
    this->paused = true;

    // Initialize Status
    this->statusMessage = "";
    this->statusPanel = new Panel(applicationStateManager, 912.5, 150, 267.5, 245, this->statusMessage, 24, sf::Color(0, 0, 0, 0), 1);
    this->stateManager->getCurrentState()->addStateElement(statusPanel);
}

SketchContainer::~SketchContainer() {}

bool SketchContainer::isPaused()
{
    return this->paused;
}

void SketchContainer::setPaused(bool signal)
{
    this->paused = signal;
}

Panel *SketchContainer::getStatusPanel()
{
    return this->statusPanel;
}