#pragma once

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <sketches/sketch_container.hpp>

class Cell : public StateElement
{
public:
    Cell(StateManager *applicationStateManager, float x, float y, float width, float height);
    ~Cell();

    void update();
    void setDistance(int distance);
    void setType(int newType);
    sf::RectangleShape *getCellShape();
    sf::Text *getCellText();

private:
    int distanceValue;
    float width, height;
    float x, y;
    int type;
};

class Grid : public SketchContainer
{
public:
    Grid(StateManager *applicationStateManager, float x, float y, float width, float height, Action algorithm);
    ~Grid();

    void create();
    void reset();
    void update();

private:
    // Data structure related variables
    std::vector<std::vector<Cell *>> cellList;
    // cells per column (number of rows)
    int heightCells;
    // cells per row (number of columns)
    int widthCells;
    std::vector<std::vector<int>> cellDistance;

    // Algorithm related variables
    Action algorithmType;
    bool completed;

    // Position and size
    float gridWidth, gridHeight;
    float cellWidth, cellHeight, cellOffset;
    sf::Vector2f firstCellPosition;

    void createDrawableList();
    void depthFirstSearch();
    void breadthFirstSearch();
    void aStar();
};