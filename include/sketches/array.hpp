#pragma once

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <state_elements/panel.hpp>
#include <sketches/sketch_container.hpp>

class Bar
{
private:
    int value;
    float height, width;
    sf::Color color;

public:
    Bar(int value, int arraySize, float barWidth, float areaHeight)
    {
        this->value = value;
        this->width = barWidth;
        this->height = value * 6;
        this->color = sf::Color::Black;
    }

    void setColor(sf::Color newColor)
    {
        this->color = newColor;
    }
    sf::Color getColor()
    {
        return color;
    }
    int getHeight()
    {
        return height;
    }
    int getWidth()
    {
        return width;
    }
    int getValue()
    {
        return this->value;
    }
    void setValue(int newValue)
    {
        this->value = newValue;
    }
};

class Array : public SketchContainer
{
public:
    std::vector<Bar *> barList;
    sf::Text statusText;
    int outer, inner;
    float arrayWidth, arrayHeight;
    float barWidth, barHeight, barOffset;
    float x, y;
    Action action;
    int size;
    int minimumIndex;
    bool sorted;
    std::string statusMessage;

    Array(StateManager *applicationStateManager, float x, float y, float width, float height, Action action);
    ~Array();

    int getOuter();
    int getInner();
    void setOuter(int i);
    void setInner(int j);

    void create();
    void reset();
    void update();

    void createDrawableList();
    void createFromInput();

    void bubbleSort();
    void insertionSort();
    void selectionSort();
};