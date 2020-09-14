#include <managers/window_manager.hpp>

WindowManager::WindowManager()
{
    this->setupWindow("Window", 1200, 800);
}

WindowManager::WindowManager(const std::string &windowTitle, unsigned int windowWidth, unsigned int windowHeight)
{
    this->setupWindow(windowTitle, windowWidth, windowHeight);
}

WindowManager::~WindowManager()
{
    this->terminateWindow();
}

bool WindowManager::isRunning()
{
    return this->running;
}

void WindowManager::clearWindow()
{
    this->window.clear(sf::Color(245, 245, 245, 255));
}

void WindowManager::displayWindow()
{
    this->window.display();
}

void WindowManager::update()
{
}

sf::RenderWindow *WindowManager::getRenderWindow()
{
    return &(this->window);
}

void WindowManager::render(const sf::Drawable &drawable)
{
    this->window.draw(drawable);
}

void WindowManager::terminateWindow()
{
    this->running = false;
    this->window.close();
}

void WindowManager::changeFPS(int delta)
{
    this->window.setFramerateLimit(this->fps + delta);
    if (this->fps >= 100)
        fps = 100;
    if (this->fps <= 5)
        fps = 5;
}
void WindowManager::setupWindow(const std::string &windowTitle, unsigned int windowWidth, unsigned int windowHeight)
{
    this->windowTitle = windowTitle;
    this->windowSize = sf::Vector2u(windowWidth, windowHeight);
    this->running = true;
    createWindow();
}
void WindowManager::createWindow()
{
    this->fps = 30;
    this->window.create({this->windowSize.x, this->windowSize.y, 32}, this->windowTitle);
    this->window.setFramerateLimit(fps);
    this->window.setVerticalSyncEnabled(false);
}
