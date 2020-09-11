#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class WindowManager
{
public:
    WindowManager();
    WindowManager(const std::string &windowTitle, unsigned int windowWidth, unsigned int windowHeight);
    ~WindowManager();

    //Check if the screen is running
    bool isRunning();

    // Prepare the screen for current tick
    void clearWindow();

    // Display the contents for current tick
    void displayWindow();

    // Check window updates
    void update();

    // Return address of SFML RenderWindow member
    sf::RenderWindow *getRenderWindow();

    void render(const sf::Drawable &drawable);

    void terminateWindow();

private:
    void setupWindow(const std::string &windowTitle, unsigned int windowWidth, unsigned int windowHeight);
    void createWindow();

    sf::RenderWindow window;
    sf::Vector2u windowSize;
    std::string windowTitle;
    bool running;
};