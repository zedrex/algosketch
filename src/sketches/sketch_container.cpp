#include <sketches/array.hpp>

SketchContainer::SketchContainer(StateManager *applicationStateManager, float x, float y, float width, float height, ActionParameter parameter)
    : StateElement(applicationStateManager, x, y, width, height)
{
    this->algorithmType = parameter;
    this->paused = true;
}
SketchContainer::~SketchContainer() {}

bool SketchContainer::isPaused() { return paused; }
void SketchContainer::setPaused(bool signal) { paused = signal; }