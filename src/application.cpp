#include <application.hpp>
#include <debugger.hpp>

sf::Font globalFont;

Application::Application() : windowManager("Application", 1200, 800)
{
    // initialize Window, Event manager, State Manager, Resource Manager
    this->stateManager.setWindowManager(&(this->windowManager));
    this->stateManager.setEventManager(&(this->eventManager));
    this->stateManager.setResourceManager(&(this->resourceManager));
    this->stateManager.start();

    globalFont.loadFromFile("assets/font/minecraft.otf");
    debug("Font loaded.");
    debug("Application Loaded.");

    srand(time(nullptr));
}

Application::~Application() {}

void Application::run()
{
    while (this->windowManager.isRunning())
    {
        this->handleInput();
        this->update();
        this->render();
    }
}

void Application::handleInput()
{
}

void Application::update()
{
    this->windowManager.update();
    this->stateManager.update();
}

void Application::render()
{
    this->windowManager.clearWindow();
    this->stateManager.render();
    this->windowManager.displayWindow();
}
