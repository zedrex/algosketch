#include <state_elements/panel.hpp>

Panel::Panel(StateManager *applicationStateManager, float x, float y, float width, float height, std::string panelLabel, int fontSize, sf::Color color) : StateElement(applicationStateManager, x, y, width, height)
{

    this->text->setString(panelLabel);
    this->text->setFont(globalFont);
    this->text->setFillColor(sf::Color::Black);
    this->text->setCharacterSize(fontSize);

    this->shape->setFillColor(color);

    // Center the text
    centerTextOnShape();
}

Panel::~Panel() {}

void Panel::update()
{
    centerTextOnShape();
}

void Panel::setString(std::string newString)
{
    this->text->setString(newString);
}