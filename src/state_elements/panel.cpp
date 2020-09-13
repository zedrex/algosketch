#include <state_elements/panel.hpp>

Panel::Panel(StateManager *applicationStateManager, float x, float y, float width, float height, std::string panelLabel, int fontSize, sf::Color color, int panelType) : StateElement(applicationStateManager, x, y, width, height)
{
    // Set text and shape
    this->text->setString(panelLabel);
    this->text->setFont(globalFont);
    this->text->setFillColor(sf::Color::Black);
    this->text->setCharacterSize(fontSize);
    this->shape->setFillColor(color);

    // Set type
    this->panelType = panelType;

    // Center the text
    if (this->panelType == 0)
        centerTextOnShape();
    else if (this->panelType == 1)
        leftAlignTextOnShape();
}

Panel::~Panel() {}

void Panel::update()
{
    if (this->panelType == 0)
        centerTextOnShape();
    else if (this->panelType == 1)
        leftAlignTextOnShape();
}

void Panel::setString(std::string newString)
{
    this->text->setString(newString);
}