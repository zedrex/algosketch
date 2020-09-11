#include<state_elements/button.hpp>

Button::Button(StateManager *applicationStateManager, float x, float y, float width, float height, std::string buttonLabel, Action action)
    : StateElement(applicationStateManager, x, y, width, height)
{

    this->buttonAction = action;

    // Choose color
    this->defaultColor = sf::Color::Black;
    this->hoverColor = sf::Color(150, 150, 150, 255);
    this->clickedColor = sf::Color(150, 255, 150, 255);

    // Initialize
    this->shape->setFillColor(defaultColor);
    this->text->setString(buttonLabel);
    this->text->setFont(globalFont);
    this->text->setFillColor(sf::Color::White);
    this->text->setCharacterSize(30);

    centerTextOnShape();
}

Button::~Button() {}

void Button::update()
{
    centerTextOnShape();
    if (clicked())
    {
        this->shape->setFillColor(this->clickedColor);
        this->stateManager->perform(this->buttonAction);
    }

    else if (hovered())
    {
        this->shape->setFillColor(this->hoverColor);
    }

    else
    {
        this->shape->setFillColor(this->defaultColor);
    }
}