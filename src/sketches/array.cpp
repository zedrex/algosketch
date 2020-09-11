#include <sketches/array.hpp>

Array::Array(StateManager *applicationStateManager, float x, float y, float width, float height, int size, ActionParameter parameter)
    : SketchContainer(applicationStateManager, x, y, width, height, parameter)
{
    std::cout << "Array Loading" << std::endl;

    this->barOffset = 1;
    this->size = size;
    this->x = x;
    this->y = y;
    this->barWidth = width / size - barOffset;
    this->arrayHeight = height;

    reset();
    std::cout << "Array Loaded" << std::endl;
}

Array::~Array()
{
    for (auto bar : barList)
        delete bar;
}

int Array::getOuter() { return outer; }
int Array::getInner() { return inner; }
void Array::setOuter(int i) { outer = i; }
void Array::setInner(int j) { inner = j; }

void Array::reset()
{
    if (paused)
    {
        outer = 0;
        inner = 0;
        sorted = false;

        barList.clear();

        for (int i = 0; i < size; i++)
            barList.push_back(new Bar(rand() % 100, size, this->barWidth, this->arrayHeight));
    }
}

void Array::draw()
{
    int offset = 1;
    temporaryDrawableList.clear();
    for (int i = 0; i < size; i++)
    {
        sf::RectangleShape *barShape = new sf::RectangleShape(sf::Vector2f(barList[i]->getWidth(), barList[i]->getHeight()));
        temporaryDrawableList.push_back(barShape);

        barShape->setPosition(this->x + (offset + barList[i]->getWidth()) * i,
                              this->y + this->arrayHeight - barList[i]->getHeight());

        if (i == getOuter())
            barShape->setFillColor(sf::Color::Green);
        else if (i == getInner())
            barShape->setFillColor(sf::Color::Blue);
        else
            barShape->setFillColor(barList[i]->getColor());

        barShape->setOutlineColor(sf::Color(200, 200, 200, 255));
        barShape->setOutlineThickness(1);
    }
}

void Array::update()
{

    draw();
    if (!paused)
        bubbleSort();
    if (sorted)
        paused = true;
}

void Array::bubbleSort()
{

    int i = getOuter();
    int j = getInner();

    if (i == size and j == size)
    {
        sorted = true;
    }

    if (!sorted)
    {

        if (barList[i]->getVal() > barList[j]->getVal())
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
    }
}