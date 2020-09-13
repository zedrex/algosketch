#include <states/graph_sketch_menu.hpp>

#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>
#include <sketches/graph.hpp>

GraphSketchMenu::GraphSketchMenu(StateManager *applicationStateManager, Action action) : State(applicationStateManager)
{
    // Top Area
    if (action == Action::GraphDepthFirstSearch)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Graph - Depth First Search", 32, sf::Color(100, 100, 100, 100)));
    }
    if (action == Action::GraphBreadthFirstSearch)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Graph - Breadth First Search", 32, sf::Color(100, 100, 100, 100)));
    }
    if (action == Action::GraphDijkstra)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Graph - Dijkstra's Shortest Path", 32, sf::Color(100, 100, 100, 100)));
    }

    // Visualization Area
    sketchContainer = new Graph(this->stateManager, 10, 70, 882.5, 660, 50, action); // 882.5
    stateElementList.push_back(sketchContainer);

    // Input Area
    stateElementList.push_back(new Panel(this->stateManager, 902.5, 70, 287.5, 660, "", 32, sf::Color(100, 100, 100, 100)));
    stateElementList.push_back(new Panel(this->stateManager, 912.5, 80, 267.5, 50, "Input:", 32, sf::Color(100, 100, 100, 0)));
    this->stateTextForm = new TextForm(this->stateManager, 912.5, 150, 267.5, 520, 24, sf::Color::White);
    stateElementList.push_back(this->stateTextForm);
    stateElementList.push_back(new Button(this->stateManager, 902.5, 680, 287.5, 50, "Create", Action::Create));

    // Bottom Area
    stateElementList.push_back(new Button(this->stateManager, 10, 740, 287.5, 50, "Reset", Action::Reset));
    stateElementList.push_back(new Button(this->stateManager, 307.5, 740, 287.5, 50, "Run", Action::Run));
    stateElementList.push_back(new Button(this->stateManager, 605, 740, 287.5, 50, "Pause", Action::Pause));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 740, 287.5, 50, "Back", Action::Back));
}

GraphSketchMenu::~GraphSketchMenu() {}

SketchContainer *GraphSketchMenu::getSketchContainer()
{
    return sketchContainer;
}