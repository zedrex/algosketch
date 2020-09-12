#include <managers/state_manager.hpp>

#include <states/main_menu.hpp>
#include <states/new_sketch_menu.hpp>
#include <states/array_sketch_menu.hpp>
#include <states/array_sort_menu.hpp>
StateManager::StateManager()
{
    this->currentState = nullptr;
}

StateManager::StateManager(WindowManager *applicationWindowManager, EventManager *applicationEventManager, ResourceManager *applicationResourceManager)
{
    setWindowManager(applicationWindowManager);
    setEventManager(applicationEventManager);
    setResourceManager(applicationResourceManager);
    this->perform(Action::ChangeToMainMenu);
}

StateManager::~StateManager()
{
    delete this->currentState;
}

void StateManager::setWindowManager(WindowManager *applicationWindowManager)
{
    this->windowManager = applicationWindowManager;
}

void StateManager::setEventManager(EventManager *applicationEventManager)
{
    this->eventManager = applicationEventManager;
}

void StateManager::setResourceManager(ResourceManager *applicationResourceManager)
{
    this->resourceManager = applicationResourceManager;
}

void StateManager::start()
{
    this->perform(Action::ChangeToMainMenu);
}

State *StateManager::getCurrentState()
{
    return this->currentState;
}

WindowManager *StateManager::getApplicationWindow()
{
    return this->windowManager;
}

EventManager *StateManager::getEventManager()
{
    return this->eventManager;
}

void StateManager::perform(Action action)
{
    switch (action)
    {
    case Action::ChangeToMainMenu:
    case Action::Back:
        changeState(new MainMenu(this));
        break;

    case Action::ChangeToNewSketchMenu:
        changeState(new NewSketchMenu(this));
        break;

    case Action::BubbleSort:
        changeState(new ArraySketchMenu(this,Action::BubbleSort));
        break;
    case Action::SelectionSort:
        changeState(new ArraySketchMenu(this,Action::SelectionSort));
        break;
    case Action::InsertionSort:
        changeState(new ArraySketchMenu(this,Action::InsertionSort));
        break;

    case Action::Array:
        changeState(new ArraySortMenu(this));
        break;
    case Action::Run:
        getCurrentState()->getSketchContainer()->setPaused(false);
        break;

    case Action::Pause:
        getCurrentState()->getSketchContainer()->setPaused(true);
        break;

    case Action::Reset:
        getCurrentState()->getSketchContainer()->reset();
        break;

    case Action::QuitApplication:
        this->getApplicationWindow()->terminateWindow();

    default:
        break;
    }
}

void StateManager::changeState(State *newState)
{
    delete this->currentState;
    currentState = nullptr;
    this->currentState = newState;
}

void StateManager::update()
{
    if (this->currentState != nullptr)
        this->currentState->update();
}

void StateManager::render()
{
    if (this->currentState != nullptr)
        this->currentState->render();
}