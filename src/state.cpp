#include <state.hpp>
#include <state_element.hpp>
#include <state_manager.hpp>
#include <array_sketch.hpp>

//DEBUG
#include <iostream>
using namespace std;

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

MainMenu::MainMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    cout << "Main Menu" << endl;
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "AlgoSketch", 104, sf ::Color(0, 0, 0, 0)));
    stateElementList.push_back(new Button(this->stateManager, 425, 460, 350, 50, "New Sketch", Action::ChangeToNewSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 520, 350, 50, "Load Sketch", Action::ChangeToLoadSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 580, 350, 50, "Options", Action::ChangeToOptionsMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 640, 350, 50, "Quit", Action::QuitApplication));
}

MainMenu::~MainMenu() {}

NewSketchMenu::NewSketchMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    cout << "New Sketch Menu" << endl;
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "Choose Data Structure", 52, sf::Color(0, 0, 0, 0)));
    stateElementList.push_back(new Button(this->stateManager, 425, 430, 350, 50, "Array", Action::Array));
    stateElementList.push_back(new Button(this->stateManager, 425, 490, 350, 50, "Graph", Action::Graph));
    stateElementList.push_back(new Button(this->stateManager, 425, 550, 350, 50, "Grid", Action::Grid));
    stateElementList.push_back(new Button(this->stateManager, 425, 610, 350, 50, "String", Action::String));
    stateElementList.push_back(new Button(this->stateManager, 425, 670, 350, 50, "Back", Action::ChangeToMainMenu));
}

NewSketchMenu::~NewSketchMenu() {}

ArraySketchMenu::ArraySketchMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    cout << "Array Sketch Menu" << endl;

    // Top Area
    stateElementList.push_back(new Panel(this->stateManager, 10, 10, 892.5, 50, "Array - Bubble Sort", 14, sf::Color::White));

    //Visualization Area
    sketchContainer = new Array(this->stateManager, 10, 70, 900, 660, 50);
    stateElementList.push_back(sketchContainer);

    // Input Area
    stateElementList.push_back(new Panel(this->stateManager, 902.5, 70, 270, 660, "", 24, sf::Color(100, 100, 100, 100)));
    stateElementList.push_back(new TextForm(this->stateManager, 912.5, 80, 250, 640, 24, sf::Color::White));
    stateElementList.push_back(new Button(this->stateManager, 912.5, 640, 287.5, 50, "Create", Action::Reset));

    // Bottom Area
    stateElementList.push_back(new Button(this->stateManager, 10, 740, 287.5, 50, "Reset", Action::Reset));
    stateElementList.push_back(new Button(this->stateManager, 307.5, 740, 287.5, 50, "Run", Action::Run));
    stateElementList.push_back(new Button(this->stateManager, 605, 740, 287.5, 50, "Pause", Action::Pause));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 740, 287.5, 50, "Back", Action::Back));
}

ArraySketchMenu::~ArraySketchMenu() {}

SketchContainer *ArraySketchMenu::getSketchContainer()
{
    return sketchContainer;
}