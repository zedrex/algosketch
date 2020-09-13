#include <sketches/grid.hpp>

// Cell functions
Cell::Cell(StateManager *applicationStateManager, Grid *grid, float x, float y, float width, float height, int graphX, int graphY)
    : StateElement(applicationStateManager, x, y, width, height)
{
    // Set mother grid
    this->motherGrid = grid;

    // Type of cell (0 = unvisited, 1 = this->cellList, 2 = obstruction)
    this->type = 0;

    // Set graph coordinates
    this->graphX = graphX;
    this->graphY = graphY;

    // Set the initial distance
    this->distanceValue = -1;
    this->text->setCharacterSize(17);
    this->text->setFillColor(sf::Color::Black);
    this->text->setFont(globalFont);
    this->text->setString("INF");

    // Set Position and size
    this->shape->setPosition(x, y);
    this->shape->setSize(sf::Vector2f(width, height));
    this->update();
}

Cell::~Cell() {}

int Cell::sourceX = -1;
int Cell::sourceY = -1;
int Cell::destinationX = -1;
int Cell::destinationY = -1;

void Cell::update()
{
    // Update text and color based on type
    if (this->type == 0) // unvisited
    {
        this->text->setString("INF");
        this->shape->setFillColor(sf::Color::White);
    }
    else if (this->type == 1) // this->cellList
    {
        this->text->setString(std::to_string(this->distanceValue));
        this->shape->setFillColor(sf::Color(100, 100, 100)); // Light Gray
    }
    else if (this->type == 2) // obstruction
    {
        this->shape->setFillColor(sf::Color::Black);
    }
    centerTextOnShape();

    // Update type based on click
    if (hovered() and rightKeyHeld())
    {
        if (this->type == 0)
        {
            this->type = 2;
        }
    }

    if (hovered() and rightKeyPressed())
    {
        if (this->type == 2)
        {
            this->type = 0;
        }
    }

    if (clicked())
    {
        if (sourceX == -1 and sourceY == -1)
        {

            sourceX = this->graphX;
            sourceY = this->graphY;
            std::cout << "Source Set" << std::endl;
        }
        else if (destinationX == -1 and destinationY == -1)
        {
            destinationX = this->graphX;
            destinationY = this->graphY;
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
    sourceX = x;
    sourceY = y;

    if (this->motherGrid->getAlgorithm() == Action::GridBreadthFirstSearch)
        this->motherGrid->setPaused(false);
}
void Cell::setDestination(int x, int y)
{
    destinationX = x;
    destinationY = y;
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
    std::cout << "Grid Loading" << std::endl;

    this->algorithmType = algorithm;
    this->gridWidth = width;
    this->gridHeight = height;

    this->paused = true;

    this->sourceX = -1;
    this->sourceY = -1;
    this->destinationX = -1;
    this->destinationY = -1;

    std::cout << "Grid loaded" << std::endl;
}

Grid::~Grid()
{
    for (int i = 0; i < this->heightCells; i++)
        for (int j = 0; j < this->widthCells; j++)
            delete this->cellList[i][j];
}

int Grid::dx[] = {0, 0, 1, -1};
int Grid::dy[] = {1, -1, 0, 0};

void Grid::create() {}

void Grid::reset()
{
    std::cout << "Resetting" << std::endl;

    this->heightCells = 10;
    this->widthCells = 10;
    this->cellOffset = 3;

    this->firstCellPosition = sf::Vector2f(10, 70);

    std::cout << "Visited vector loading" << std::endl;

    // // Visited vector initialization
    // this->cellDistance.clear();
    // std::vector<int> blankCells(widthCells, -1);
    // std::vector<std::vector<int>> gridVector;
    // for (int i = 0; i < heightCells; i++)
    //     this->cellDistance.push_back(blankCells);

    std::cout << "Cell size loading" << std::endl;
    // Calculate cell size
    this->cellWidth = (this->gridWidth / this->widthCells) - this->cellOffset;
    this->cellHeight = (this->gridHeight / this->heightCells) - this->cellOffset;

    std::cout << "Cell list loading" << std::endl;
    if (this->paused)
    {
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
        this->completed = false;
    }

    std::cout << "Drawable list loading" << std::endl;
    createDrawableList();
    std::cout << "Drawable list loaded" << std::endl;
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
    if (!this->paused and this->algorithmType == Action::GridBreadthFirstSearch)
        this->breadthFirstSearch();
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

void Grid::createSource()
{
    this->sourceX = this->cellList[0][0]->sourceX;
    this->sourceY = this->cellList[0][0]->sourceY;

    if (this->sourceX >= 0 and this->sourceX < heightCells and this->sourceY >= 0 and this->sourceY < widthCells)
    {
        this->cellList[this->sourceX][this->sourceY]->setType(1);
        this->cellList[this->sourceX][this->sourceY]->setDistance(0);
        this->bfsQueue.push({this->sourceX, this->sourceY});
    }

    std::cout << "Source: " << this->sourceX << " " << this->sourceY << std::endl;
}
void Grid::createDestination()
{
    this->destinationX = this->cellList[0][0]->destinationX;
    this->destinationY = this->cellList[0][0]->destinationY;
}

void Grid::breadthFirstSearch()
{
    if (!this->bfsQueue.empty())
    {
        int px = bfsQueue.front().first;
        int py = bfsQueue.front().second;
        bfsQueue.pop();

        for (int i = 0; i < 4; i++)
        {
            int x = px + this->dx[i];
            int y = py + this->dy[i];
            if (this->cellList[x][y]->getType() == 0 and x >= 0 and x < heightCells and y >= 0 and y < widthCells)
            {
                this->cellList[x][y]->setDistance(this->cellList[px][py]->getDistance() + 1);
                this->cellList[x][y]->setType(1);
                bfsQueue.push({x, y});
            }
        }
    }
    else if (bfsQueue.empty())
    {
        completed = true;
    }
}

void Grid::depthFirstSearch() {}
void Grid::aStar() {}
