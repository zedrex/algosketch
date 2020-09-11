#include <state_element.hpp>
#include <state_manager.hpp>
#include <sstream>

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
    this->text->setOrigin((textBounds.width - shapeBounds.x) / 2 + textBounds.left,
                          (textBounds.height - shapeBounds.y) / 2 + textBounds.top);
    this->text->setPosition(this->shape->getPosition().x, this->shape->getPosition().y);
}

void StateElement::leftAlignTextOnShape()
{
    // Text wrap version (Spaghetti)
    this->text->setPosition(this->shape->getPosition().x + 10, this->shape->getPosition().y - 20);

    // Real version
    // this->text->setPosition(this->shape->getPosition().x + 10, this->shape->getPosition().y + 10);
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
    if (hovered() and leftKeyPressed())
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

bool StateElement::leftKeyPressed()
{
    return this->stateManager->getEventManager()->isLeftKeyPressed();
}

bool StateElement::leftKeyReleased()
{
    return this->stateManager->getEventManager()->isLeftKeyReleased();
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
    leftAlignTextOnShape();

    //Check text input
    std::string currentText = this->getTextInput();

    if (currentText == "\b")
    {
        if (this->keyboardInput.size() != 1)
            this->keyboardInput = this->keyboardInput.substr(0, this->keyboardInput.size() - 1);
    }
    else if (currentText == "\r")
    {
        this->keyboardInput += "\n";
    }
    else
    {
        this->keyboardInput += currentText;

        // Text wrap (Spaghetti version)
        size_t textSize = this->keyboardInput.size();
        if (textSize % 18 == 0 and this->keyboardInput[textSize - 1] != '\n')
            this->keyboardInput += "\n";
    }

    //Finalize the text string
    this->text->setString(this->keyboardInput + "_");
}

std::string TextForm::getText()
{
    return this->keyboardInput;
}

// Extract integers from the text
std::vector<int> TextForm::extractValues()
{
    std::vector<int> integers;
    std::stringstream textStream;
    std::string streamWord;
    int extractedInteger;

    textStream << this->getText();

    while (!textStream.eof())
    {
        // Load each word into a string
        textStream >> streamWord;

        // Convert to integer and push it to the vector
        if (std::stringstream(streamWord) >> extractedInteger)
            integers.push_back(extractedInteger);
    }
    return integers;
}
