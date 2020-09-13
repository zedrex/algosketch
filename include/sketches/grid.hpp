#pragma once

#include <queue>
#include <utility>

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <sketches/sketch_container.hpp>

class Grid;

class Cell : public StateElement
{
public:
    Cell(StateManager *applicationStateManager, Grid *grid, float x, float y, float width, float height, int graphX, int graphY);
    ~Cell();

    void update();

    void setDistance(int distance);
    int getDistance();
    void setType(int newType);
    int getType();
    void setSource(int x, int y);
    void setDestination(int x, int y);

    static int sourceX, sourceY, destinationX, destinationY;

    sf::RectangleShape *getCellShape();
    sf::Text *getCellText();

private:
    Grid *motherGrid;
    int distanceValue;
    float width, height;
    int graphX, graphY;
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

    Action getAlgorithm();

private:
    // Data structure related variables
    std::vector<std::vector<Cell *>> cellList;
    // BFS Queue
    std::queue<std::pair<int, int>> bfsQueue;
    // Cells per column (number of rows)
    int heightCells;
    // Cells per row (number of columns)
    int widthCells;
    std::vector<std::vector<int>> cellDistance;

    // Algorithm related variables
    Action algorithmType;
    bool processing, completed;
    int sourceX, sourceY, destinationX, destinationY;

    // Position and size
    float gridWidth, gridHeight;
    float cellWidth, cellHeight, cellOffset;
    sf::Vector2f firstCellPosition;

    // Direction arrays
    static int dx[4];
    static int dy[4];

    void createDrawableList();
    void createSource();
    void createDestination();

    void depthFirstSearch();
    void breadthFirstSearch();
    void aStar();
};