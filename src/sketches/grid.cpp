#include <sketches/grid.hpp>

// Cell functions
Cell::Cell(StateManager *applicationStateManager, float x, float y, float width, float height)
    : StateElement(applicationStateManager, x, y, width, height)
{
    // Type of cell (0 = unvisited, 1 = visited, 2 = obstruction)
    this->type = 0;

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

void Cell::update()
{
    // Update text and type based on distance
    if (this->distanceValue == -1)
    {
        this->text->setString("INF");
    }
    else
    {
        this->text->setString(std::to_string(this->distanceValue));
        this->type = 1;
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

    // Update color based on type
    if (this->type == 0) // unvisited
        this->shape->setFillColor(sf::Color::White);
    else if (this->type == 1) // visited
        this->shape->setFillColor(sf::Color(100, 100, 100));
    else if (this->type == 2) // obstruction
        this->shape->setFillColor(sf::Color::Black);
}

void Cell::setDistance(int distance)
{
    this->distanceValue = distance;
}

void Cell::setType(int newType)
{
    this->type = newType;
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
    std::cout << "Resetting" << std::endl;
    reset();
    std::cout << "Grid loaded" << std::endl;
}

Grid::~Grid()
{
    for (int i = 0; i < this->heightCells; i++)
        for (int j = 0; j < this->widthCells; j++)
            delete this->cellList[i][j];
}

void Grid::create() {}

void Grid::reset()
{

    this->heightCells = 13; // cells per column (number of rows)
    this->widthCells = 15;  // cells per row (number of columns)
    this->cellOffset = 3;

    this->firstCellPosition = sf::Vector2f(10, 70);

    std::cout << "Visited vector loading" << std::endl;

    // Visited vector initialization
    this->cellDistance.clear();
    std::vector<int> blankCells(widthCells, -1);
    std::vector<std::vector<int>> gridVector;
    for (int i = 0; i < heightCells; i++)
        this->cellDistance.push_back(blankCells);

    std::cout << "Cell size loading" << std::endl;
    // Calculate cell size
    this->cellWidth = (this->gridWidth / this->widthCells) - this->cellOffset;
    this->cellHeight = (this->gridHeight / this->heightCells) - this->cellOffset;

    std::cout << cellWidth << " " << cellHeight << std::endl;

    std::cout << "Cell List loading" << std::endl;
    if (this->paused)
    {
        // Load the cells with positions in the cell vector
        for (int i = 0; i < heightCells; i++)
        {
            std::vector<Cell *> cellLine;
            for (int j = 0; j < widthCells; j++)
            {
                cellLine.push_back(new Cell(stateManager, this->firstCellPosition.x + (this->cellWidth + this->cellOffset) * j, this->firstCellPosition.y + (this->cellHeight + this->cellOffset) * i, this->cellWidth, this->cellHeight));
                //   cellLine.push_back(new Cell(stateManager, this->firstCellPosition.x + (this->cellWidth + this->cellOffset) * i, this->firstCellPosition.y + (this->cellHeight + this->cellOffset) * j, 10, 10));
            }
            this->cellList.push_back(cellLine);
        }
        this->completed = false;
    }
    std::cout << "Drawable list loading" << std::endl;
    createDrawableList();
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

void Grid::depthFirstSearch() {}
void Grid::breadthFirstSearch() {}
void Grid::aStar() {}
