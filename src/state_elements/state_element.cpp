#include <state_elements/state_element.hpp>
#include <managers/state_manager.hpp>

extern sf::Font globalFont;

StateElement::StateElement(StateManager *applicationStateManager, float x, float y, float width, float height)
{
    this->stateManager = applicationStateManager;
    shape = new sf::RectangleShape;
    text = new sf::Text;

    this->shape->setPosition(sf::Vector2f(x, y));
    this->shape->setSize(sf::Vector2f(width, height));
    this->shape->setFillColor(sf::Color(255, 255, 255, 0));

    this->drawableList.push_back(shape);
    this->drawableList.push_back(text);
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
    // this->text->setPosition(this->shape->getPosition().x + 10, this->shape->getPosition().y - 20);

    // Real version
    this->text->setPosition(this->shape->getPosition().x + 10, this->shape->getPosition().y + 10);
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

bool StateElement::leftKeyHeld()
{
    return this->stateManager->getEventManager()->isLeftKeyHeld();
}

bool StateElement::rightKeyPressed()
{
    return this->stateManager->getEventManager()->isRightKeyPressed();
}

bool StateElement::rightKeyReleased()
{
    return this->stateManager->getEventManager()->isRightKeyReleased();
}

bool StateElement::rightKeyHeld()
{
    return this->stateManager->getEventManager()->isRightKeyHeld();
}

std::string StateElement::getTextInput()
{
    return this->stateManager->getEventManager()->getCurrentKey();
}