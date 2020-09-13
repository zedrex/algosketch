#include <states/array_algorithm_menu.hpp>

#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>

ArrayAlgorithmMenu::ArrayAlgorithmMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "Choose Sorting Algorithm", 52, sf::Color(0, 0, 0, 0), 1));

    stateElementList.push_back(new Button(this->stateManager, 425, 370, 350, 50, "Bubble Sort", Action::BubbleSort));
    stateElementList.push_back(new Button(this->stateManager, 425, 430, 350, 50, "Selection Sort", Action::SelectionSort));
    stateElementList.push_back(new Button(this->stateManager, 425, 490, 350, 50, "Insertion Sort", Action::InsertionSort));
    stateElementList.push_back(new Button(this->stateManager, 425, 550, 350, 50, "Shell Sort", Action::ShellSort));
    stateElementList.push_back(new Button(this->stateManager, 425, 610, 350, 50, "Gnome Sort", Action::GnomeSort));
    stateElementList.push_back(new Button(this->stateManager, 425, 670, 350, 50, "Back", Action::ChangeToNewSketchMenu));
}

ArrayAlgorithmMenu::~ArrayAlgorithmMenu() {}