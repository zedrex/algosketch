#include <managers/state_manager.hpp>

#include <states/main_menu.hpp>
#include <states/new_sketch_menu.hpp>
#include <states/array_sketch_menu.hpp>
#include <states/array_algorithm_menu.hpp>
#include <states/graph_sketch_menu.hpp>
#include <states/graph_algorithm_menu.hpp>
#include <states/grid_sketch_menu.hpp>
#include <states/grid_algorithm_menu.hpp>

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

    case Action::Array:
        changeState(new ArrayAlgorithmMenu(this));
        break;

    case Action::BubbleSort:
        changeState(new ArraySketchMenu(this, Action::BubbleSort));
        break;

    case Action::SelectionSort:
        changeState(new ArraySketchMenu(this, Action::SelectionSort));
        break;

    case Action::InsertionSort:
        changeState(new ArraySketchMenu(this, Action::InsertionSort));
        break;

    case Action::GnomeSort:
        changeState(new ArraySketchMenu(this, Action::GnomeSort));
        break;

    case Action::ShellSort:
        changeState(new ArraySketchMenu(this, Action::ShellSort));
        break;
        
    case Action::Graph:
        changeState(new GraphAlgorithmMenu(this));
        break;

    case Action::GraphDepthFirstSearch:
        changeState(new GraphSketchMenu(this, Action::GraphDepthFirstSearch));
        break;

    case Action::GraphBreadthFirstSearch:
        changeState(new GraphSketchMenu(this, Action::GraphBreadthFirstSearch));
        break;

    case Action::GraphDijkstra:
        changeState(new GraphSketchMenu(this, Action::GraphDijkstra));
        break;

    case Action::Grid:
        changeState(new GridAlgorithmMenu(this));
        break;

    case Action::GridDepthFirstSearch:
        changeState(new GridSketchMenu(this, Action::GridDepthFirstSearch));
        break;

    case Action::GridBreadthFirstSearch:
        changeState(new GridSketchMenu(this, Action::GridBreadthFirstSearch));
        break;

    case Action::GridDijkstra:
        changeState(new GridSketchMenu(this, Action::GridDijkstra));
        break;

    case Action::Create:
        getCurrentState()->getSketchContainer()->create();
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