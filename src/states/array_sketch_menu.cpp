#include <states/array_sketch_menu.hpp>
#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>

ArraySketchMenu::ArraySketchMenu(StateManager *applicationStateManager, ActionParameter algorithmType) : State(applicationStateManager)
{
    // Top Area
    std::string algorithmName;
    if (algorithmType == ActionParameter::InsertionSort)
        algorithmName = "Insertion Sort";
    else if (algorithmType == ActionParameter::SelectionSort)
        algorithmName = "Selection Sort";
    else if (algorithmType == ActionParameter::BubbleSort)
        algorithmName = "Bubble Sort";
    stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - " + algorithmName, 32, sf::Color::White));

    // Visualization Area
    sketchContainer = new Array(this->stateManager, 10, 70, 882.5, 660, 50, algorithmType); // 882.5
    stateElementList.push_back(sketchContainer);

    // Input Area
    stateElementList.push_back(new Panel(this->stateManager, 902.5, 70, 287.5, 660, "", 32, sf::Color(100, 100, 100, 100)));
    stateElementList.push_back(new Panel(this->stateManager, 912.5, 80, 267.5, 50, "Input:", 32, sf::Color(100, 100, 100, 0)));
    stateElementList.push_back(new TextForm(this->stateManager, 912.5, 150, 267.5, 520, 24, sf::Color::White));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 680, 287.5, 50, "Create", ActionType::Reset, ActionParameter::Null));

    // Bottom Area
    stateElementList.push_back(new Button(this->stateManager, 10, 740, 287.5, 50, "Reset", ActionType::Reset, ActionParameter::Null));
    stateElementList.push_back(new Button(this->stateManager, 307.5, 740, 287.5, 50, "Run", ActionType::Run, ActionParameter::Null));
    stateElementList.push_back(new Button(this->stateManager, 605, 740, 287.5, 50, "Pause", ActionType::Pause, ActionParameter::Null));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 740, 287.5, 50, "Back", ActionType::Back, ActionParameter::Null));
}

ArraySketchMenu::~ArraySketchMenu() {}

SketchContainer *ArraySketchMenu::getSketchContainer()
{
    return sketchContainer;
}