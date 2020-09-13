#include <states/main_menu.hpp>
#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>

MainMenu::MainMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    // Title
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "AlgoSketch", 104, sf ::Color(0, 0, 0, 0), 0));

    // Buttons
    stateElementList.push_back(new Button(this->stateManager, 425, 460, 350, 50, "New Sketch", Action::ChangeToNewSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 520, 350, 50, "Load Sketch", Action::ChangeToLoadSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 580, 350, 50, "Options", Action::ChangeToOptionsMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 640, 350, 50, "Quit", Action::QuitApplication));
}

MainMenu::~MainMenu() {}