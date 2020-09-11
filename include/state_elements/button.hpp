#include <state_elements/state_element.hpp>

class Button : public StateElement
{
public:
    Button(StateManager *applicationStateManager, float x, float y, float width, float height, std::string buttonLabel, ActionType actionType, ActionParameter actionParameter);
    ~Button();

    void update();

private:
    sf::Color defaultColor;
    sf::Color hoverColor;
    sf::Color clickedColor;
    ActionType buttonActionType;
    ActionParameter buttonActionParameter;
};