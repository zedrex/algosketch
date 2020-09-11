#include <managers/application.hpp>

sf::Font globalFont;

Application::Application() : windowManager("Application", 1200, 800), eventManager(&(this->stateManager))
{
    // initialize Window, Event manager, State Manager, Resource Manager
    this->stateManager.setWindowManager(&(this->windowManager));
    this->stateManager.setEventManager(&(this->eventManager));
    this->stateManager.setResourceManager(&(this->resourceManager));
    this->stateManager.start();

    globalFont.loadFromFile("assets/font/minecraft.otf");

    srand(time(nullptr));
}

Application::~Application() {}

void Application::run()
{
    while (this->windowManager.isRunning())
    {
        this->update();
        this->render();
    }
}

void Application::update()
{
    this->windowManager.update();
    this->eventManager.update();
    this->stateManager.update();
}

void Application::render()
{
    this->windowManager.clearWindow();
    this->stateManager.render();
    this->windowManager.displayWindow();
}
