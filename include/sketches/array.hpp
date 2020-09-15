#pragma once

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <state_elements/panel.hpp>
#include <sketches/sketch_container.hpp>

class Array;

class Bar
{
public:
    friend class Array;
    Bar(int value, int arraySize, float barWidth, float areaHeight);
    ~Bar();
    void setColor(sf::Color newColor);
    sf::Color getColor();
    int getHeight();
    int getWidth();
    int getValue();
    void setValue(int newValue);

private:
    int value;
    float height, width;
    sf::Color color;
};

class Array : public SketchContainer
{
public:
    Array(StateManager *applicationStateManager, float x, float y, float width, float height, Action action);
    ~Array();

    void create();
    void reset();
    void update();

    void createDrawableList();
    void createFromInput();

private:
    std::vector<Bar *> barList;
    int outer, inner;
    float arrayWidth, arrayHeight;
    float barWidth, barHeight, barOffset;
    float x, y;
    Action action;
    int size;
    int minimumIndex;
    bool sorted;

    // For Shell Sort
    int gap;
    bool gapSet = false;

    int getOuter();
    int getInner();
    void setOuter(int i);
    void setInner(int j);

    void bubbleSort();
    void insertionSort();
    void selectionSort();
    void shellSort();
    void gnomeSort();
};