#pragma once

#include <state_elements/state_element.hpp>

class Panel : public StateElement
{
public:
    Panel(StateManager *applicationStateManager, float x, float y, float width, float height, std::string panelLabel, int fontSize, sf::Color color, int panelType);
    ~Panel();

    void update();
    void setString(std::string newString);

private:
    int panelType;
};