#pragma once

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <sketches/sketch_container.hpp>

class Bar
{
private:
    int value;
    float height, width;
    sf::Color color;

public:
    Bar()
    {
        value = 0;
        height = 0;
        width = 0;
        color = sf::Color::Black;
    }
    Bar(int value, int arraySize, float barWidth, float areaHeight)
    {
        this->value = value;
        this->width = barWidth;
        this->height = value * 6;
        color = sf::Color::Black;
    }

    void setColor(sf::Color col)
    {
        color = col;
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
    int getVal()
    {
        return value;
    }
};

class Array : public SketchContainer
{
public:
    std::vector<Bar *> barList;
    int outer, inner;
    float arrayWidth, arrayHeight;
    float barWidth, barHeight, barOffset;
    float x, y;
    Action action;
    int size;
    int min_idx;
    Bar *key;
    //min_idx used for selection sort
    //key used for insertion sort
    bool sorted;

    Array(StateManager *applicationStateManager, float x, float y, float width, float height, int size, Action action);
    ~Array();

    int getOuter();
    int getInner();
    void setOuter(int i);
    void setInner(int j);

    void create();
    void reset();
    void update();

    void createDrawableList();

    void bubbleSort();
    void insertionSort();
    void selectionSort();
};