#include <window.hpp>

Window::Window()
{
    setup("Window", sf::Vector2u(1200, 800));
}

Window::Window(const std::string &title, const sf::Vector2u &size)
{
    setup(title, size);
}

Window::~Window()
{
    terminate();
}

bool Window::isRunning()
{
    return this->running;
}

void Window::clearScreen()
{
    this->window.clear(sf::Color(200, 200, 200, 255));
}
void Window::displayScreen()
{
    this->window.display();
}

void Window::update()
{
    sf::Event event;
    while (this->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            this->running = false;
    }
}

sf::RenderWindow *Window::getRenderWindow()
{
    return &(this->window);
}

void Window::render(const sf::Drawable &l_drawable)
{
    this->window.draw(l_drawable);
}

void Window::setup(const std::string &l_title, const sf::Vector2u &l_size)
{
    this->windowTitle = l_title;
    this->windowSize = l_size;
    this->running = true;
    create();
}
void Window::create()
{
    this->window.create({this->windowSize.x, this->windowSize.y, 32}, this->windowTitle);
}

void Window::terminate()
{
    this->window.close();
}
