#include <states/grid_algorithm_menu.hpp>
#include <states/graph_algorithm_menu.hpp>

#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>

GridAlgorithmMenu::GridAlgorithmMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "Choose Grid Algorithm", 52, sf::Color(0, 0, 0, 0), 0));

    stateElementList.push_back(new Button(this->stateManager, 425, 430, 350, 50, "Breadth First Search", Action::GridBreadthFirstSearch));
    stateElementList.push_back(new Button(this->stateManager, 425, 490, 350, 50, "A* Pathfinder", Action::GridAStarPathfinder));
    stateElementList.push_back(new Button(this->stateManager, 425, 550, 350, 50, "Depth First Search", Action::GridDepthFirstSearch));
    stateElementList.push_back(new Button(this->stateManager, 425, 610, 350, 50, "Back", Action::ChangeToNewSketchMenu));
}

GridAlgorithmMenu::~GridAlgorithmMenu() {}