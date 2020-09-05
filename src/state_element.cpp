#include <state_element.hpp>
#include <state_manager.hpp>

//DEBUG
#include <iostream>
using namespace std;
//DEBUG

extern sf::Font globalFont;

StateElement::StateElement(StateManager *applicationStateManager, float x, float y, float width, float height)
{
    std::cout << "State Element Loading" << std::endl;
    this->stateManager = applicationStateManager;
    shape = new sf::RectangleShape;
    text = new sf::Text;

    this->shape->setPosition(sf::Vector2f(x, y));
    this->shape->setSize(sf::Vector2f(width, height));
    this->shape->setFillColor(sf::Color(255, 255, 255, 0));

    drawableList.push_back(shape);
    drawableList.push_back(text);
    std::cout << "State Element Loaded" << std::endl;
}

StateElement::~StateElement()
{
    for (auto drawable : drawableList)
        delete drawable;
}
std::vector<sf::Drawable *> *StateElement::getDrawableList()
{
    return &(this->drawableList);
}
std::vector<sf::Drawable *> *StateElement::getTemporaryDrawableList()
{
    return &(this->temporaryDrawableList);
}

void StateElement::centerTextOnShape()
{
    const sf::FloatRect textBounds(this->text->getLocalBounds());
    const sf::Vector2f shapeBounds(this->shape->getSize());
    this->text->setOrigin((textBounds.width - shapeBounds.x) / 2 + textBounds.left, (textBounds.height - shapeBounds.y) / 2 + textBounds.top);
    this->text->setPosition(this->shape->getPosition().x, this->shape->getPosition().y);
}

bool StateElement::hovered()
{
    if (this->shape->getGlobalBounds().contains(getMousePosition().x, getMousePosition().y))
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
    return this->stateManager->getEventManager()->getMousePosition();
}

std::string StateElement::getTextInput()
{
    return this->stateManager->getEventManager()->getCurrentKey();
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
        cout << "Clicked" << endl;
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

TextForm::TextForm(StateManager *applicationStateManager, float x, float y, float width, float height, int fontSize, sf::Color color) : StateElement(applicationStateManager, x, y, width, height)
{
    this->text->setString("");
    this->text->setFont(globalFont);
    this->text->setFillColor(sf::Color::Black);
    this->text->setCharacterSize(fontSize);

    this->shape->setFillColor(color);

    this->keyboardInput = "";
}

TextForm::~TextForm()
{
}

void TextForm::update()
{
    this->keyboardInput += this->getTextInput();
    this->text->setString(this->keyboardInput);
}

std::string TextForm::getText()
{
    return this->keyboardInput;
}
