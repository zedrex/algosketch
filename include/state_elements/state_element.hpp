#pragma once

#include <SFML/Graphics.hpp>
#include <managers/state_manager.hpp>

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
    // Text Alignment
    void centerTextOnShape();
    void leftAlignTextOnShape();

    // Action
    bool hovered();
    bool clicked();

    // Input
    sf::Vector2i getMousePosition();
    bool leftKeyPressed();
    bool leftKeyReleased();
    bool leftKeyHeld();
    bool rightKeyPressed();
    bool rightKeyReleased();
    std::string getTextInput();

    StateManager *stateManager;
    std::vector<sf::Drawable *> drawableList, temporaryDrawableList;
    sf::Text *text;
    sf::RectangleShape *shape;
};
