#pragma once

#include <SFML/Graphics.hpp>

class Window
{
public:
    Window();
    Window(const std::string &l_title, const sf::Vector2u &l_size);
    ~Window();

    //Check if the screen is running
    bool isRunning();

    // Prepare the screen for current tick
    void clearScreen();

    // Display the contents for current tick
    void displayScreen();

    // Check window updates
    void update();

    // Return address of SFML RenderWindow member
    sf::RenderWindow *getRenderWindow();

    void render(const sf::Drawable &drawable);

private:
    void setup(const std::string &l_title, const sf::Vector2u &l_size);
    void create();
    void terminate();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    bool running;
};