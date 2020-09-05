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

    // Returns pointer to the drawables
    std::vector<sf::Drawable *> *getDrawableList();
    std::vector<sf::Drawable *> *getTemporaryDrawableList();

protected:
    // Center the text
    void centerTextOnShape();
    bool hovered();

    bool clicked();

    // Global mouse cursor coordinates
    sf::Vector2i getMousePosition();

    StateManager *stateManager;
    std::vector<sf::Drawable *> drawableList, temporaryDrawableList;
    sf::Text *text;
    sf::RectangleShape *shape;
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

class TextForm : public StateElement
{
public:
    TextForm(StateManager *applicationStateManager, float x, float y, float width, float height, int fontSize, sf::Color color);
    ~TextForm();

    void update();
    std::string getText();

private:
    std::string keyboardInput;
};