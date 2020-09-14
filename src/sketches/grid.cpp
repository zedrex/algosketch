#include <sketches/grid.hpp>
#include <states/grid_algorithm_menu.hpp>

// Cell functions
Cell::Cell(StateManager *applicationStateManager, Grid *grid, float x, float y, float width, float height, int graphX, int graphY)
    : StateElement(applicationStateManager, x, y, width, height)
{
    // Set mother grid
    this->motherGrid = grid;

    // Type of cell (0 = unvisited, 1 = visited, 2 = obstruction, 3 = source, 4 = destination, 5 = path)
    this->type = 0;

    // Set graph coordinates
    this->graphX = graphX;
    this->graphY = graphY;

    // Set the initial distance
    this->distanceValue = -1;
    this->text->setCharacterSize(height / 2);
    this->text->setFillColor(sf::Color::Black);
    this->text->setFont(globalFont);
    this->text->setString("");

    // Set Position and size
    this->shape->setPosition(x, y);
    this->shape->setSize(sf::Vector2f(width, height));
    this->update();
}

Cell::~Cell() {}

void Cell::update()
{
    // Update text and color based on type
    if (this->type == 0) // unvisited
    {
        this->text->setString("");
        this->shape->setFillColor(sf::Color::White);
    }
    else if (this->type == 2) // obstruction
    {
        this->shape->setFillColor(sf::Color::Black);
    }
    else if (this->type == 3) // source
    {
        if (this->distanceValue == -1)
            this->text->setString("");
        else
            this->text->setString(std::to_string(this->distanceValue));
        this->shape->setFillColor(sf::Color(0, 191, 255));
        this->text->setFillColor(sf::Color::White);
    }
    else if (this->type == 4) // destination
    {
        if (this->distanceValue == -1)
            this->text->setString("");
        else
            this->text->setString(std::to_string(this->distanceValue));

        this->shape->setFillColor(sf::Color(34, 139, 34)); // Forest Green
        this->text->setFillColor(sf::Color::White);
    }
    else if (this->type == 5) // path
    {
        this->text->setString(std::to_string(this->distanceValue));
        this->shape->setFillColor(sf::Color(255 - this->distanceValue * 2, 69 - this->distanceValue, 0)); // Brick red
        this->text->setFillColor(sf::Color::White);
    }
    else if (this->type == 1) // visited
    {
        this->text->setString(std::to_string(this->distanceValue));
        if (this->motherGrid->getAlgorithm() == Action::GridDepthFirstSearch)
            this->shape->setFillColor(sf::Color(0, 255, 255 - this->distanceValue));
        else
            this->shape->setFillColor(sf::Color(0, 255 - this->distanceValue, 255 - this->distanceValue * 4)); // Blue to green

        this->text->setFillColor(sf::Color::Black);
    }
    centerTextOnShape();

    // // If paused, show borders
    // if (this->motherGrid->paused)
    // {
    //     this->shape->setOutlineColor(sf::Color::Black);
    //     this->shape->setOutlineThickness(0.5);
    // }
    // else
    // {
    //     this->shape->setOutlineThickness(0);
    // }

    // Update type based on click when no algorithm is initialized
    if (!this->motherGrid->algorithmInitialized)
    {
        // Obstruction by right clicking unvisited cells
        if (hovered() and rightKeyHeld())
        {
            if (this->type == 0)
            {
                this->type = 2;
            }
        }

        // Undo obstruction by right clicking obstruction
        if (hovered() and rightKeyPressed())
        {
            if (this->type == 2)
            {
                this->type = 0;
            }
        }

        // Create source by left clicking when grid does not have source
        if (clicked() and this->type == 0 and this->motherGrid->sourceX == -1 and this->motherGrid->sourceY == -1)
        {
            setSource(this->graphX, this->graphY);
        }

        // Create destination by left clicking when grid does not have destination
        else if (clicked() and this->type == 0 and this->motherGrid->destinationX == -1 and this->motherGrid->destinationY == -1)
        {
            setDestination(this->graphX, this->graphY);
        }
    }
}

void Cell::setDistance(int distance)
{
    this->distanceValue = distance;
}
int Cell::getDistance()
{
    return this->distanceValue;
}

void Cell::setType(int newType)
{
    this->type = newType;
}
int Cell::getType()
{
    return this->type;
}

void Cell::setSource(int x, int y)
{
    this->type = 3; // source
    this->motherGrid->sourceX = this->graphX;
    this->motherGrid->sourceY = this->graphY;

    // Start the algorithm if it's DFS or BFS
    if (this->motherGrid->algorithmType == Action::GridFloodFill or this->motherGrid->algorithmType == Action::GridDepthFirstSearch)
    {
        this->motherGrid->paused = false;
    }
}
void Cell::setDestination(int x, int y)
{
    this->type = 4; // destination
    this->motherGrid->destinationX = this->graphX;
    this->motherGrid->destinationY = this->graphY;

    // Start the algorithm if it's A* Pathfinding
    if (this->motherGrid->algorithmType == Action::GridBreadthFirstSearchPathfinding)
    {
        this->motherGrid->paused = false;
    }
}

sf::RectangleShape *Cell::getCellShape()
{
    return this->shape;
}

sf::Text *Cell::getCellText()
{
    return this->text;
}

// Grid functions
Grid::Grid(StateManager *applicationStateManager, float x, float y, float width, float height, Action algorithm)
    : SketchContainer(applicationStateManager, x, y, width, height)
{

    this->algorithmType = algorithm;
    this->widthCells = 0;
    this->heightCells = 0;
    this->gridWidth = width;
    this->gridHeight = height;
    this->cellOffset = 3;
    this->firstCellPosition = sf::Vector2f(x, y);

    this->paused = true;
    this->initialized = false;
    this->algorithmInitialized = false;
    this->completed = false;

    this->sourceX = -1;
    this->sourceY = -1;
    this->destinationX = -1;
    this->destinationY = -1;
}

Grid::~Grid()
{
    for (int i = 0; i < this->heightCells; i++)
        for (int j = 0; j < this->widthCells; j++)
            delete this->cellList[i][j];
}

int Grid::dx[] = {0, 0, 1, -1};
int Grid::dy[] = {1, -1, 0, 0};

void Grid::create()
{
    if (this->paused)
    { // Clear previous outputs
        this->temporaryDrawableList.clear();
        this->cellList.clear();

        // Set all the sizes
        this->createFromInput();
        this->cellWidth = (this->gridWidth / this->widthCells) - this->cellOffset;
        this->cellHeight = (this->gridHeight / this->heightCells) - this->cellOffset;

        // Initialize the variables
        this->algorithmInitialized = false;
        this->completed = false;
        this->sourceX = -1;
        this->sourceY = -1;
        this->destinationX = -1;
        this->destinationY = -1;

        // Load the cells with positions in the cell vector
        for (int i = 0; i < heightCells; i++)
        {
            std::vector<Cell *> cellLine;
            for (int j = 0; j < widthCells; j++)
            {
                cellLine.push_back(new Cell(stateManager, this, this->firstCellPosition.x + (this->cellWidth + this->cellOffset) * j, this->firstCellPosition.y + (this->cellHeight + this->cellOffset) * i, this->cellWidth, this->cellHeight, i, j));
                //   cellLine.push_back(new Cell(stateManager, this->firstCellPosition.x + (this->cellWidth + this->cellOffset) * i, this->firstCellPosition.y + (this->cellHeight + this->cellOffset) * j, 10, 10));
            }
            this->cellList.push_back(cellLine);
        }
        createDrawableList();
        this->initialized = true;
    }
}

void Grid::reset()
{
    if (this->paused and this->initialized)
    {
        // Clear previous outputs
        this->temporaryDrawableList.clear();
        this->cellList.clear();

        // Initialize the variables
        this->algorithmInitialized = false;
        this->completed = false;
        this->sourceX = -1;
        this->sourceY = -1;
        this->destinationX = -1;
        this->destinationY = -1;

        // Load the cells with positions in the cell vector
        for (int i = 0; i < heightCells; i++)
        {
            std::vector<Cell *> cellLine;
            for (int j = 0; j < widthCells; j++)
            {
                cellLine.push_back(new Cell(stateManager, this, this->firstCellPosition.x + (this->cellWidth + this->cellOffset) * j, this->firstCellPosition.y + (this->cellHeight + this->cellOffset) * i, this->cellWidth, this->cellHeight, i, j));
                //   cellLine.push_back(new Cell(stateManager, this->firstCellPosition.x + (this->cellWidth + this->cellOffset) * i, this->firstCellPosition.y + (this->cellHeight + this->cellOffset) * j, 10, 10));
            }
            this->cellList.push_back(cellLine);
        }
        createDrawableList();
    }
}

void Grid::update()
{

    for (int i = 0; i < this->heightCells; i++)
    {
        for (int j = 0; j < this->widthCells; j++)
        {
            //int cellType = this->cellList[i][j]->getCellType();
            //this->cellList[i][j]->setDistance(this->cellDistance[i][j]);
            this->cellList[i][j]->update();
        }
    }
    // Select corresponding algorithm
    if (!this->paused and this->algorithmType == Action::GridDepthFirstSearch)
        this->depthFirstSearch();
    if (!this->paused and this->algorithmType == Action::GridFloodFill)
        this->floodFill();
    if (!this->paused and this->algorithmType == Action::GridBreadthFirstSearchPathfinding)
        this->breadthFirstSearchPathfinding();
    if (this->completed)
        this->paused = true;
}

Action Grid::getAlgorithm()
{
    return this->algorithmType;
}

void Grid::createDrawableList()
{
    temporaryDrawableList.clear();
    for (int i = 0; i < this->heightCells; i++)
    {
        for (int j = 0; j < this->widthCells; j++)
        {
            temporaryDrawableList.push_back(this->cellList[i][j]->getCellShape());
            temporaryDrawableList.push_back(this->cellList[i][j]->getCellText());
        }
    }
}

void Grid::createFromInput()
{
    std::vector<int> values = this->stateManager->getCurrentState()->getTextForm()->extractValues();
    // Ignore invalid input size
    if (values.size() >= 2)
    {
        this->heightCells = values[0];
        this->widthCells = values[1];
    }
}

void Grid::createSource()
{
    if (this->algorithmType == Action::GridFloodFill or this->algorithmType == Action::GridBreadthFirstSearchPathfinding)
    {
        if (this->sourceX >= 0 and this->sourceX < heightCells and this->sourceY >= 0 and this->sourceY < widthCells)
        {
            this->cellList[this->sourceX][this->sourceY]->setType(3);
            this->cellList[this->sourceX][this->sourceY]->setDistance(0);
            this->bfsQueue.push({this->sourceX, this->sourceY});
        }
    }
    else if (this->algorithmType == Action::GridDepthFirstSearch)
    {
        if (this->sourceX >= 0 and this->sourceX < heightCells and this->sourceY >= 0 and this->sourceY < widthCells)
        {
            this->cellList[this->sourceX][this->sourceY]->setType(3);
            this->cellList[this->sourceX][this->sourceY]->setDistance(0);
            this->dfsStack.push_front({this->sourceX, this->sourceY});
        }
    }
}

void Grid::createDestination()
{
}

void Grid::floodFill()
{
    if (!this->algorithmInitialized)
    {
        createSource();
        this->algorithmInitialized = true;
    }
    if (!this->bfsQueue.empty())
    {
        std::pair<int, int> currentInQueue = this->bfsQueue.front();
        std::pair<int, int> lastInQueue = this->bfsQueue.back();
        while (!this->bfsQueue.empty() and ((this->bfsQueue.size() != 1 and currentInQueue != lastInQueue) or this->bfsQueue.size() == 1))
        {
            currentInQueue = this->bfsQueue.front();
            int px = currentInQueue.first;
            int py = currentInQueue.second;
            bfsQueue.pop();

            for (int i = 0; i < 4; i++)
            {
                int cx = px + this->dx[i];
                int cy = py + this->dy[i];
                if (cx >= 0 and cx < heightCells and cy >= 0 and cy < widthCells)
                {
                    if (this->cellList[cx][cy]->getType() == 0)
                    {
                        this->cellList[cx][cy]->setDistance(this->cellList[px][py]->getDistance() + 1);
                        this->cellList[cx][cy]->setType(1);
                        bfsQueue.push({cx, cy});
                    }
                }
            }
        }
    }
    else if (bfsQueue.empty())
    {
        this->paused = true;
        this->completed = true;
    }
}

void Grid::depthFirstSearch()
{
    if (!this->algorithmInitialized)
    {
        createSource();
        this->algorithmInitialized = true;
    }
    if (!this->dfsStack.empty())
    {
        std::pair<int, int> currentInStack = this->dfsStack.front();
        std::pair<int, int> lastInStack = this->dfsStack.back();

        currentInStack = this->dfsStack.front();
        int px = currentInStack.first;
        int py = currentInStack.second;
        dfsStack.pop_front();

        for (int i = 0; i < 4; i++)
        {
            int cx = px + this->dx[i];
            int cy = py + this->dy[i];
            if (cx >= 0 and cx < heightCells and cy >= 0 and cy < widthCells)
            {
                if (this->cellList[cx][cy]->getType() == 0)
                {
                    this->cellList[cx][cy]->setDistance(this->cellList[px][py]->getDistance() + 1);
                    this->cellList[cx][cy]->setType(1);
                    dfsStack.push_front({cx, cy});
                }
            }
        }
    }
    else if (dfsStack.empty())
    {
        this->paused = true;
        this->completed = true;
    }
}

void Grid::breadthFirstSearchPathfinding()
{
    if (!this->algorithmInitialized)
    {
        createSource();
        this->algorithmInitialized = true;
    }
    if (!this->bfsQueue.empty())
    {
        std::pair<int, int> currentInQueue = this->bfsQueue.front();
        std::pair<int, int> lastInQueue = this->bfsQueue.back();
        while (!this->bfsQueue.empty() and ((this->bfsQueue.size() != 1 and currentInQueue != lastInQueue) or this->bfsQueue.size() == 1))
        {
            currentInQueue = this->bfsQueue.front();
            int px = currentInQueue.first;
            int py = currentInQueue.second;
            bfsQueue.pop();

            for (int i = 0; i < 4; i++)
            {
                int cx = px + this->dx[i];
                int cy = py + this->dy[i];
                if (cx >= 0 and cx < heightCells and cy >= 0 and cy < widthCells)
                {
                    if (this->cellList[cx][cy]->getType() == 0)
                    {
                        this->cellList[cx][cy]->setDistance(this->cellList[px][py]->getDistance() + 1);
                        this->cellList[cx][cy]->setType(1);
                        bfsQueue.push({cx, cy});
                    }
                    else if (this->cellList[cx][cy]->getType() == 4)
                    {
                        this->cellList[cx][cy]->setDistance(this->cellList[px][py]->getDistance() + 1);
                        while (!bfsQueue.empty())
                            bfsQueue.pop();
                        break;
                    }
                }
            }
        }
    }
    else if (bfsQueue.empty())
    {
        // Initialize variables to trace a path
        std::pair<int, int> targetCell, currentCell;
        currentCell = {this->destinationX, this->destinationY};
        int targetDistance = this->cellList[this->destinationX][this->destinationY]->getDistance() - 1;

        // Trace path by backtracking
        this->cellList[this->destinationX][this->destinationY]->setType(5);
        while (targetDistance >= 0)
        {
            int px = currentCell.first;
            int py = currentCell.second;

            for (int i = 0; i < 4; i++)
            {
                int cx = px + this->dx[i];
                int cy = py + this->dy[i];

                if (cx >= 0 and cx < heightCells and cy >= 0 and cy < widthCells)
                {
                    if (this->cellList[cx][cy]->getDistance() == targetDistance)
                    {
                        targetDistance--;
                        this->cellList[cx][cy]->setType(5);

                        currentCell = {cx, cy};
                        continue;
                    }
                }
            }
        }

        this->paused = true;
        this->completed = true;
    }
}

float Grid::getGeometricDistance(int x1, int y1, int x2, int y2)
{
    float distance = std::sqrt(float(x2 - x1) * float(x2 - x1) + float(y2 - y1) * float(y2 - y1));
    distance = distance * 100.0;
    distance = int(distance);
    return distance / 100.0;
}