#include <states/grid_sketch_menu.hpp>

#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>
#include <sketches/grid.hpp>

GridSketchMenu::GridSketchMenu(StateManager *applicationStateManager, Action action) : State(applicationStateManager)
{
    // Top Area
    if (action == Action::GridDepthFirstSearch)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Grid - Depth First Search", 32, sf::Color(100, 100, 100, 100), 0));
    }
    if (action == Action::GridBreadthFirstSearch)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Grid - Breadth First Search", 32, sf::Color(100, 100, 100, 100), 0));
    }
    if (action == Action::GridAStarPathfinder)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Grid - A-Star Pathfinder", 32, sf::Color(100, 100, 100, 100), 0));
    }

    // Slow down the application
    this->stateManager->getApplicationWindow()->changeFPS(-25);

    // Visualization Area
    sketchContainer = new Grid(this->stateManager, 10, 70, 882.5, 660, action); // 882.5
    stateElementList.push_back(sketchContainer);

    // Input Area
    stateElementList.push_back(new Panel(this->stateManager, 902.5, 70, 287.5, 660, "", 32, sf::Color(100, 100, 100, 100), 1));
    stateElementList.push_back(new Panel(this->stateManager, 912.5, 80, 267.5, 50, "Input:", 32, sf::Color(100, 100, 100, 0), 1));
    this->stateTextForm = new TextForm(this->stateManager, 912.5, 150, 267.5, 520, 24, sf::Color::White);
    stateElementList.push_back(this->stateTextForm);
    stateElementList.push_back(new Button(this->stateManager, 902.5, 680, 287.5, 50, "Create", Action::Create));

    // Bottom Area
    stateElementList.push_back(new Button(this->stateManager, 10, 740, 287.5, 50, "Reset", Action::Reset));
    stateElementList.push_back(new Button(this->stateManager, 307.5, 740, 287.5, 50, "Run", Action::Run));
    stateElementList.push_back(new Button(this->stateManager, 605, 740, 287.5, 50, "Pause", Action::Pause));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 740, 287.5, 50, "Back", Action::Grid));
}

GridSketchMenu::~GridSketchMenu() {}

SketchContainer *GridSketchMenu::getSketchContainer()
{
    return sketchContainer;
}