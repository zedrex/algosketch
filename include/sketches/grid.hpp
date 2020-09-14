#pragma once

#include <queue>
#include <deque>
#include <utility>
#include <map>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <sketches/sketch_container.hpp>

class Grid;

class Cell : public StateElement
{
public:
    friend class Grid;

    Cell(StateManager *applicationStateManager, Grid *grid, float x, float y, float width, float height, int graphX, int graphY);
    ~Cell();

    void update();

    void setDistance(int distance);
    int getDistance();
    void setType(int newType);
    int getType();
    void setSource(int x, int y);
    void setDestination(int x, int y);

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
    friend class Cell;

    Grid(StateManager *applicationStateManager, float x, float y, float width, float height, Action algorithm);
    ~Grid();

    void create();
    void reset();
    void update();

    Action getAlgorithm();

private:
    // Data structure related variables
    std::vector<std::vector<Cell *>> cellList;
    //  Additional DS for algorithms
    std::queue<std::pair<int, int>> bfsQueue;
    std::deque<std::pair<int, int>> dfsStack;

    // Cells per column (number of rows)
    int heightCells;
    // Cells per row (number of columns)
    int widthCells;

    // Algorithm related variables
    Action algorithmType;
    bool processing, completed;
    bool algorithmInitialized;
    int sourceX, sourceY, destinationX, destinationY;

    // Position and size
    float gridWidth, gridHeight;
    float cellWidth, cellHeight, cellOffset;
    sf::Vector2f firstCellPosition;

    // Direction arrays
    static int dx[4];
    static int dy[4];

    void createDrawableList();
    void createFromInput();
    void createSource();
    void createDestination();

    void depthFirstSearch();
    void breadthFirstSearch();
    void aStarPathfinder();
    void theRealAStar();

    float getGeometricDistance(int x1, int y1, int x2, int y2);
};