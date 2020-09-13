#include <states/array_sketch_menu.hpp>

#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>
#include <sketches/sketch_container.hpp>
#include <sketches/array.hpp>

ArraySketchMenu::ArraySketchMenu(StateManager *applicationStateManager, Action action) : State(applicationStateManager)
{
    // Top Area
    if (action == Action::BubbleSort)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - Bubble Sort", 32, sf::Color(100, 100, 100, 100), 0));
    }
    if (action == Action::SelectionSort)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - Selection Sort", 32, sf::Color(100, 100, 100, 100), 0));
    }
    if (action == Action::InsertionSort)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - Insertion Sort", 32, sf::Color(100, 100, 100, 100), 0));
    }
    if (action == Action::ShellSort)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - Shell Sort", 32, sf::Color(100, 100, 100, 100), 0));
    }
    if (action == Action::GnomeSort)
    {
        stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - Gnome Sort", 32, sf::Color(100, 100, 100, 100), 0));
    }
    // Visualization Area
    this->sketchContainer = new Array(this->stateManager, 10, 70, 882.5, 660, action); // 882.5
    stateElementList.push_back(this->sketchContainer);
    stateElementList.push_back(this->sketchContainer->getStatusPanel());

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
    stateElementList.push_back(new Button(this->stateManager, 902.5, 740, 287.5, 50, "Back", Action::Array));
}

ArraySketchMenu::~ArraySketchMenu() {}

SketchContainer *ArraySketchMenu::getSketchContainer()
{
    return sketchContainer;
}