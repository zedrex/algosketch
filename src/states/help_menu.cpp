#include <states/help_menu.hpp>

#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>

HelpMenu::HelpMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Help", 32, sf::Color(200, 200, 200), 0));
    stateElementList.push_back(new Panel(this->stateManager, 210, 70, 1180, 730, "General:\nControl algorithm speed using mouse wheel.\n\nArray Algorithms:\nInput the array size only.\nClicking Reset will shuffle the array.\n\nGrid Algorithms:\nInput number of rows and columns.\nLeft Click to set source and destination.\nRight Click to create obstructions.", 36, sf::Color(100, 100, 100, 0), 1));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 740, 287.5, 50, "Back", Action::ChangeToMainMenu));
}

HelpMenu::~HelpMenu() {}