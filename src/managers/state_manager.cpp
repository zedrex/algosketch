#include <managers/state_manager.hpp>
#include <states/main_menu.hpp>
#include <states/new_sketch_menu.hpp>
#include <states/array_algorithm_menu.hpp>
#include <states/array_sketch_menu.hpp>

StateManager::StateManager()
{
    this->currentState = nullptr;
}

StateManager::StateManager(WindowManager *applicationWindowManager, EventManager *applicationEventManager, ResourceManager *applicationResourceManager)
{
    setWindowManager(applicationWindowManager);
    setEventManager(applicationEventManager);
    setResourceManager(applicationResourceManager);
    this->perform({ActionType::ChangeToMainMenu, ActionParameter::Null});
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
    this->perform({ActionType::ChangeToMainMenu, ActionParameter::Null});
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
    ActionType actionType = action.first;
    ActionParameter actionParameter = action.second;

    if (actionType == ActionType::ChangeToMainMenu or actionType == ActionType::Back)
    {
        changeState(new MainMenu(this));
    }

    else if (actionType == ActionType::ChangeToNewSketchMenu)
    {
        changeState(new NewSketchMenu(this));
    }

    else if (actionType == ActionType::ChangeToArrayMenu)
    {
        changeState(new ArraySketchMenu(this, actionParameter));
    }

    else if (actionType == ActionType::ChangeToArrayAlgorithmMenu)
    {
        changeState(new ArrayAlgorithmMenu(this));
    }

    else if (actionType == ActionType::Run)
    {
        getCurrentState()->getSketchContainer()->setPaused(false);
    }

    else if (actionType == ActionType::Pause)
    {
        getCurrentState()->getSketchContainer()->setPaused(true);
    }

    else if (actionType == ActionType::Reset)
    {
        getCurrentState()->getSketchContainer()->reset();
    }

    else if (actionType == ActionType::QuitApplication)
    {
        this->getApplicationWindow()->terminateWindow();
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