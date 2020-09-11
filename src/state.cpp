#include <state.hpp>
#include <managers/state_manager.hpp>
#include <state_elements/button.hpp>
#include <state_elements/panel.hpp>
#include <state_elements/text_form.hpp>

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
    // Title
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "AlgoSketch", 104, sf ::Color(0, 0, 0, 0)));

    // Buttons
    stateElementList.push_back(new Button(this->stateManager, 425, 460, 350, 50, "New Sketch", Action::ChangeToNewSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 520, 350, 50, "Load Sketch", Action::ChangeToLoadSketchMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 580, 350, 50, "Options", Action::ChangeToOptionsMenu));
    stateElementList.push_back(new Button(this->stateManager, 425, 640, 350, 50, "Quit", Action::QuitApplication));
}

MainMenu::~MainMenu() {}

NewSketchMenu::NewSketchMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    // Title
    stateElementList.push_back(new Panel(this->stateManager, 250, 116, 700, 250, "Choose Data Structure", 52, sf::Color(0, 0, 0, 0)));

    // Buttons
    stateElementList.push_back(new Button(this->stateManager, 425, 430, 350, 50, "Array", Action::Array));
    stateElementList.push_back(new Button(this->stateManager, 425, 490, 350, 50, "Graph", Action::Graph));
    stateElementList.push_back(new Button(this->stateManager, 425, 550, 350, 50, "Grid", Action::Grid));
    stateElementList.push_back(new Button(this->stateManager, 425, 610, 350, 50, "String", Action::String));
    stateElementList.push_back(new Button(this->stateManager, 425, 670, 350, 50, "Back", Action::ChangeToMainMenu));
}

NewSketchMenu::~NewSketchMenu() {}

ArraySketchMenu::ArraySketchMenu(StateManager *applicationStateManager) : State(applicationStateManager)
{
    // Top Area
    stateElementList.push_back(new Panel(this->stateManager, 10, 10, 1180, 50, "Array - Bubble Sort", 32, sf::Color::White));

    // Visualization Area
    sketchContainer = new Array(this->stateManager, 10, 70, 882.5, 660, 50); // 882.5
    stateElementList.push_back(sketchContainer);

    // Input Area
    stateElementList.push_back(new Panel(this->stateManager, 902.5, 70, 287.5, 660, "", 32, sf::Color(100, 100, 100, 100)));
    stateElementList.push_back(new Panel(this->stateManager, 912.5, 80, 267.5, 50, "Input:", 32, sf::Color(100, 100, 100, 0)));
    stateElementList.push_back(new TextForm(this->stateManager, 912.5, 150, 267.5, 520, 24, sf::Color::White));
    stateElementList.push_back(new Button(this->stateManager, 902.5, 680, 287.5, 50, "Create", Action::Reset));

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