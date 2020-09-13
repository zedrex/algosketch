#include <sketches/array.hpp>
#include <states/array_algorithm_menu.hpp>

Array::Array(StateManager *applicationStateManager, float x, float y, float width, float height, Action action)
    : SketchContainer(applicationStateManager, x, y, width, height)
{
    std::cout << "Array Loading" << std::endl;
    this->action = action;
    this->barOffset = 1;
    this->x = x;
    this->y = y;
    this->arrayWidth = width;
    this->arrayHeight = height;

    this->sorted = false;
    this->paused = true;

    // Initialize Text
    this->statusMessage = "";
    this->text->setPosition(10, 70);
    this->text->setString(this->statusMessage);
    this->text->setFont(globalFont);
    this->text->setFillColor(sf::Color::Black);
    this->text->setCharacterSize(27);

    std::cout << "Array Loaded" << std::endl;
}

Array::~Array()
{
    for (auto bar : barList)
        delete bar;
}

int Array::getOuter()
{
    return outer;
}
int Array::getInner()
{
    return inner;
}
void Array::setOuter(int i)
{
    outer = i;
}
void Array::setInner(int j)
{
    inner = j;
}

void Array::create()
{
    // Clear previous outputs
    this->temporaryDrawableList.clear();
    this->barList.clear();

    // Set all the sizes
    this->createFromInput();
    this->barWidth = arrayWidth / size - barOffset;
    this->arrayHeight = arrayHeight;

    // Create bars and drawables
    for (int i = 0; i < size; i++)
        barList.push_back(new Bar(rand() % 100, this->size, this->barWidth, this->arrayHeight));
    createDrawableList();

    // Initialize the variables
    this->initialized = true;
    this->outer = 0;
    this->inner = 0;
    this->minimumIndex = 0;
    this->sorted = false;
}

void Array::reset()
{
    if (this->paused and this->initialized)
    {
        // Clear previous outputs
        this->barList.clear();

        // Re-create bars and drawables
        for (int i = 0; i < size; i++)
            barList.push_back(new Bar(rand() % 100, this->size, this->barWidth, this->arrayHeight));
        createDrawableList();

        // Initialize the variables
        this->outer = 0;
        this->inner = 0;
        this->minimumIndex = 0;
        this->sorted = false;
    }
}

void Array::update()
{

    if (!paused and this->action == Action::BubbleSort)
    {
        bubbleSort();
        createDrawableList();
    }
    if (!paused and this->action == Action::InsertionSort)
    {
        insertionSort();
        createDrawableList();
    }
    if (!paused and this->action == Action::SelectionSort)
    {
        selectionSort();
        createDrawableList();
    }
    if (sorted)
        paused = true;
}

void Array::createDrawableList()
{
    int offset = 1;
    temporaryDrawableList.clear();
    for (int i = 0; i < size; i++)
    {
        sf::RectangleShape *barShape = new sf::RectangleShape(sf::Vector2f(barList[i]->getWidth(), barList[i]->getHeight()));
        temporaryDrawableList.push_back(barShape);

        barShape->setPosition(this->x + (offset + barList[i]->getWidth()) * i,
                              this->y + this->arrayHeight - barList[i]->getHeight());

        if (this->action == Action::InsertionSort)
        {
            if (i == getOuter())
                barShape->setFillColor(sf::Color::Red);
            else if (i == getInner() + 1)
                barShape->setFillColor(sf::Color::Blue);
            else
                barShape->setFillColor(barList[i]->getColor());
        }
        else
        {
            if (i == getOuter())
                barShape->setFillColor(sf::Color::Red);
            else if (i == getInner())
                barShape->setFillColor(sf::Color::Blue);
            else
                barShape->setFillColor(barList[i]->getColor());
        }

        barShape->setOutlineColor(sf::Color(200, 200, 200, 255));
        barShape->setOutlineThickness(1);
    }
    temporaryDrawableList.push_back(&(this->statusText));
}
void Array::createFromInput()
{
    std::vector<int> values = this->stateManager->getCurrentState()->getTextForm()->extractValues();
    this->size = values[0];
}

void Array::bubbleSort()
{

    int i = getOuter();
    int j = getInner();

    if (i == size and j == size)
    {
        sorted = true;
        this->statusMessage = "";
    }

    if (!sorted)
    {

        if (barList[i]->getValue() > barList[j]->getValue())
        {
            std::swap(barList[i], barList[j]);
        }

        j++;
        if (j == size)
        {
            i++;
            j = i;
        }

        setOuter(i);
        setInner(j);

        // Set status text
        this->statusMessage = "Swapped " + std::to_string(i) + " and " + std::to_string(j);
    }

    std::cout << this->statusMessage << std::endl;
    this->statusText.setString(this->statusMessage);
}

void Array::selectionSort()
{
    int i = getOuter();
    int j = getInner();

    if (i == size - 1 and j == size)
    {
        sorted = true;
    }
    if (i < size and !sorted)
    {
        if (j < size)
        {
            if (barList[minimumIndex]->getValue() > barList[j]->getValue())
            {
                minimumIndex = j;
            }
            j++;
        }
        //std::cout<<"Selection sort "<<i<<"\t"<<j<<std::endl;
        if (j == size)
        {
            std::swap(barList[i], barList[minimumIndex]);
            std::cout << "swapped " << i << "\t" << minimumIndex << std::endl;
            i++;
            minimumIndex = i;
            j = i + 1;
        }
    }

    setOuter(i);
    setInner(j);
}

void Array::insertionSort()
{
    int i = getOuter();
    int j = getInner();

    if (i == size)
    {
        sorted = true;
    }

    if (!sorted and i > 0)
    {
        if (j >= 0 and barList[j]->getValue() > barList[j + 1]->getValue())
        {
            std::swap(barList[j], barList[j + 1]);
            j--;
        }
        else
        {
            i++;
            j = i - 1;
        }
    }
    if (i == 0)
        i++;

    setInner(j);
    setOuter(i);
}