#include <state_element.hpp>
#include <state_manager.hpp>

//DEBUG
#include <iostream>
using namespace std;
//DEBUG

extern sf::Font globalFont;

StateElement::StateElement(StateManager *applicationStateManager, float x, float y, float width, float height)
{
    this->stateManager = applicationStateManager;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
}
StateElement::~StateElement()
{
}
sf::Drawable *StateElement::getShape()
{
    return &(this->shape);
}

sf::Drawable *StateElement::getText()
{
    return &(this->text);
}

void StateElement::centerTextOnShape()
{
    const sf::FloatRect textBounds(this->text.getLocalBounds());
    const sf::Vector2f shapeBounds(this->shape.getSize());
    this->text.setOrigin((textBounds.width - shapeBounds.x) / 2 + textBounds.left, (textBounds.height - shapeBounds.y) / 2 + textBounds.top);
    this->text.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
}

bool StateElement::hovered()
{
    if (this->shape.getGlobalBounds().contains(getMousePosition().x, getMousePosition().y))
        return true;
    else
        return false;
}

bool StateElement::clicked()
{
    if (hovered() and sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        return true;
    }
    else
        return false;
}

sf::Vector2i StateElement::getMousePosition()
{
    return sf::Mouse::getPosition(*(this->stateManager->getApplicationWindow()->getRenderWindow()));
}

Button::Button(StateManager *applicationStateManager, float x, float y, float width, float height, std::string buttonLabel, Action action)
    : StateElement(applicationStateManager, x, y, width, height)
{

    this->buttonAction = action;

    // Choose color
    this->defaultColor = sf::Color::Black;
    this->hoverColor = sf::Color(150, 150, 150, 255);
    this->clickedColor = sf::Color(150, 255, 150, 255);

    // Initialize
    this->shape.setFillColor(defaultColor);
    this->text.setString(buttonLabel);
    this->text.setFont(globalFont);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(30);

    centerTextOnShape();
}

Button::~Button() {}

void Button::update()
{
    centerTextOnShape();
    if (clicked())
    {
        this->shape.setFillColor(this->clickedColor);
        cout << "Clicked" << endl;
        this->stateManager->perform(this->buttonAction);
    }

    else if (hovered())
    {
        this->shape.setFillColor(this->hoverColor);
    }

    else
    {
        this->shape.setFillColor(this->defaultColor);
    }
}

Panel::Panel(StateManager *applicationStateManager, float x, float y, float width, float height, std::string panelLabel, int fontSize, sf::Color color) : StateElement(applicationStateManager, x, y, width, height)
{
    // Give color, text, font
    this->shape.setFillColor(sf::Color(200, 200, 200, 255));

    this->text.setString(panelLabel);
    this->text.setFont(globalFont);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(fontSize);

    this->shape.setFillColor(color);

    // Center the text
    centerTextOnShape();
}

Panel::~Panel() {}

void Panel::update()
{
    centerTextOnShape();
}

// Form::Form(/* args */)
// {
// }

// Form::~Form()
// {
// }

// SketchContainer::SketchContainer(/* args */)
// {
// }

// SketchContainer::~SketchContainer()
// {
// }
