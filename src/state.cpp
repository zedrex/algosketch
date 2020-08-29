#include <state.hpp>
#include <state_element.hpp>
#include <state_manager.hpp>

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
        stateManager->getApplicationWindow()->render(*stateElement->getShape());
        stateManager->getApplicationWindow()->render(*stateElement->getText());
    }
}

void State::update()
{
    for (auto stateElement : stateElementList)
    {
        stateElement->update();
    }
}

MainMenu::MainMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    cout << "Main Menu" << endl;
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "AlgoSketch", 104));
    stateElementList.push_back(new Button(this->stateManager, 425, 460, 350, 50, "New Sketch", Action::ChangeToNewSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 520, 350, 50, "Load Sketch", Action::ChangeToLoadSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 580, 350, 50, "Options", Action::ChangeToOptionsMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 640, 350, 50, "Quit", Action::QuitApplication));
}

MainMenu::~MainMenu() {}

NewSketchMenu::NewSketchMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    cout << "New Sketch Menu" << endl;
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "Choose Data Structure", 52));
    stateElementList.push_back(new Button(this->stateManager, 425, 430, 350, 50, "Array", Action::Array));
    stateElementList.push_back(new Button(this->stateManager, 425, 490, 350, 50, "Graph", Action::Graph));
    stateElementList.push_back(new Button(this->stateManager, 425, 550, 350, 50, "Grid", Action::Grid));
    stateElementList.push_back(new Button(this->stateManager, 425, 610, 350, 50, "String", Action::String));
    stateElementList.push_back(new Button(this->stateManager, 425, 670, 350, 50, "Back", Action::ChangeToMainMenu));
}

NewSketchMenu::~NewSketchMenu() {}