#pragma once

#include <SFML/Graphics.hpp>
#include <state_manager.hpp>

//Default font
extern sf::Font globalFont;

// Abstract class for GUI elements
class StateElement
{
public:
    StateElement(StateManager *applicationStateManager, float x, float y, float width, float height);
    ~StateElement();
    virtual void update() = 0;

    // Returns pointer to the drawable shape
    sf::Drawable *getShape();

    // Returns pointer to the drawable text
    sf::Drawable *getText();

protected:
    // Center the text
    void centerTextOnShape();
    bool hovered();

    bool clicked();

    // Global mouse cursor coordinates
    sf::Vector2i getMousePosition();

    StateManager *stateManager;
    sf::RectangleShape shape;
    sf::Text text;
};

class Button : public StateElement
{
public:
    Button(StateManager *applicationStateManager, float x, float y, float width, float height, std::string buttonLabel, Action action);
    ~Button();

    void update();

private:
    sf::Color defaultColor;
    sf::Color hoverColor;
    sf::Color clickedColor;
    Action buttonAction;
};

class Panel : public StateElement
{
public:
    Panel(StateManager *applicationStateManager, float x, float y, float width, float height, std::string panelLabel, int fontSize, sf::Color color);
    ~Panel();

    void update();
};

// class Form
// {
// public:
//     Form(/* args */);
//     ~Form();

//     void update();

// private:
//     /* data */
// };

// class SketchContainer : public StateElement
// {

// public:
//     SketchContainer(/* args */);
//     ~SketchContainer();
//     void update();

// private:
//     /* data */
// };

// class Array : public SketchContainer
// {
// }
