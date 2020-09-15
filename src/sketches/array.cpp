#include <sketches/array.hpp>
#include <states/array_algorithm_menu.hpp>

Array::Array(StateManager *applicationStateManager, float x, float y, float width, float height, Action action)
    : SketchContainer(applicationStateManager, x, y, width, height)
{
    this->action = action;
    this->barOffset = 0.85;
    this->x = x;
    this->y = y;
    this->arrayWidth = width;
    this->arrayHeight = height;

    // Initialize variables
    this->minimumIndex = 0;
    this->gap = this->size / 2;
    this->inner = 0;
    this->outer = 0;
    this->sorted = false;
    this->paused = true;
    this->gapSet = false;
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
        barList.push_back(new Bar(rand() % 95 + 5, this->size, this->barWidth, this->arrayHeight));
    createDrawableList();

    // Initialize the variables
    this->initialized = true;
    this->minimumIndex = 0;
    this->gap = this->size / 2;
    this->inner = 0;
    this->outer = 0;
    this->gapSet = false;
    this->sorted = false;

    this->statusMessage = "Unsorted";
    this->statusPanel->setString(this->statusMessage);
}

void Array::reset()
{
    if (this->paused and this->initialized)
    {
        // Clear previous outputs
        this->barList.clear();

        // Re-create bars and drawables
        for (int i = 0; i < size; i++)
            barList.push_back(new Bar(rand() % 95 + 5, this->size, this->barWidth, this->arrayHeight));
        createDrawableList();

        // Initialize the variables
        this->minimumIndex = 0;
        this->gap = this->size / 2;
        this->inner = 0;
        this->outer = 0;
        this->gapSet = false;
        this->sorted = false;

        this->statusMessage = "Unsorted";
        this->statusPanel->setString(this->statusMessage);
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
    if (!paused and this->action == Action::ShellSort)
    {
        shellSort();
        createDrawableList();
    }

    if (!paused and this->action == Action::GnomeSort)
    {
        gnomeSort();
        createDrawableList();
    }

    if (sorted)
    {
        this->statusMessage = "Sorted";
        this->statusPanel->setString(this->statusMessage);
        paused = true;
    }
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
            if (i == getOuter() and !this->sorted)
                barShape->setFillColor(sf::Color::Red);
            else if (i == getInner() + 1 and !this->sorted)
                barShape->setFillColor(sf::Color::Blue);
            else
                barShape->setFillColor(barList[i]->getColor());
        }
        else if (this->action == Action::GnomeSort)
        {
            if (i == getOuter() and !this->sorted)
                barShape->setFillColor(sf::Color::Red);
            else
                barShape->setFillColor(barList[i]->getColor());
        }
        else
        {
            if (i == getOuter() and !this->sorted)
                barShape->setFillColor(sf::Color::Red);
            else if (i == getInner() and !this->sorted)
                barShape->setFillColor(sf::Color::Blue);
            else
                barShape->setFillColor(barList[i]->getColor());
        }

        barShape->setOutlineColor(sf::Color(200, 200, 200, 255));
        barShape->setOutlineThickness(1);
    }
}

void Array::createFromInput()
{
    std::vector<int> values = this->stateManager->getCurrentState()->getTextForm()->extractValues();
    // Ignore empty vector
    if (values.size() != 0)
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
            this->statusMessage = "Swapped " + std::to_string(i) + " and " + std::to_string(j);
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
    }

    this->statusPanel->setString(this->statusMessage);
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

        if (j == size)
        {
            this->statusMessage = "Swapped " + std::to_string(i) + " and " + std::to_string(minimumIndex) + "\nSelected index: " + std::to_string(minimumIndex);
            std::swap(barList[i], barList[minimumIndex]);
            i++;
            minimumIndex = i;
            j = i + 1;
        }
    }

    setOuter(i);
    setInner(j);

    this->statusPanel->setString(this->statusMessage);
    if (sorted)
        this->statusMessage = "";
}

void Array::insertionSort()
{
    if (!sorted)
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
                this->statusMessage = "Swapped " + std::to_string(j) + " and " + std::to_string(j + 1);
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

    if (!sorted)
        this->statusPanel->setString(this->statusMessage);
    else
        this->statusMessage = "";
}

void Array::shellSort()
{
    if (!sorted)
    {
        if (gap == size / 2 and !gapSet)
        {
            setOuter(gap);
            setInner(getOuter() - gap);
            gapSet = true;
        }
        if (gap == 0)
            sorted = true;
        if (gap > 0 and !sorted)
        {
            int j = getOuter();
            if (j <= size)
            {
                int i = getInner();
                if (i >= 0)
                {
                    if (barList[i + gap]->getValue() > barList[i]->getValue())
                    {
                        setInner(j - gap);
                        j++;
                        setOuter(j);
                    }
                    else
                    {
                        std::swap(barList[i + gap], barList[i]);
                        this->statusMessage = "Swapped " + std::to_string(i + gap) + " and " + std::to_string(i) + "\nGap = " + std::to_string(gap);
                        i -= gap;
                        setInner(i);
                    }
                }
                else
                {
                    setInner(j - gap);
                    j++;
                    setOuter(j);
                }
            }
            else
            {
                gap /= 2;
                setOuter(gap);
            }
        }
        else
        {
            sorted = true;
            gapSet = false;
            gap = size / 2;
        }
    }

    if (!sorted)
        this->statusPanel->setString(this->statusMessage);
    else
        this->statusMessage = "";
}

void Array::gnomeSort()
{
    if (!sorted)
    {
        int index = getOuter();
        if (index < size)
        {
            if (index == 0)
            {
                index++;
                setOuter(index);
            }
            if (barList[index]->getValue() >= barList[index - 1]->getValue())
            {
                index++;
                setOuter(index);
            }
            else
            {
                std::swap(barList[index], barList[index - 1]);
                this->statusMessage = "Swapped " + std::to_string(index - 1) + " and " + std::to_string(index);
                index--;
                setOuter(index);
            }
        }
        else
        {
            sorted = true;
        }
    }
    if (!sorted)
        this->statusPanel->setString(this->statusMessage);
    else
        this->statusMessage = "";
}