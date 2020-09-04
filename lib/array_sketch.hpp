#pragma once

#include <SFML/Graphics.hpp>
#include <state_element.hpp>

class SketchContainer : public StateElement
{
public:
    SketchContainer(StateManager *applicationStateManager, float x, float y, float width, float height) : StateElement(applicationStateManager, x, y, width, height)
    {
        paused = true;
    }
    ~SketchContainer() {}

    bool isPaused() { return paused; }
    void setPaused(bool signal) { paused = signal; }
    virtual void reset() = 0;

protected:
    bool paused;
};

class Bar
{
private:
    int value, height, width;
    int offset;
    sf::Color color;

public:
    Bar()
    {
        value = 0;
        height = 0;
        width = 0;
        color = sf::Color::Black;
    }
    Bar(int value, int arraySize, float areaWidth, float areaHeight)
    {
        this->offset = 1;
        this->value = value;
        this->width = areaWidth / (float)(arraySize + offset);
        this->height = value * 6;
        color = sf::Color::Black;
    }
    void setColor(sf::Color col)
    {
        color = col;
    }
    sf::Color getColor()
    {
        return color;
    }
    int getHeight()
    {
        return height;
    }
    int getWidth()
    {
        return width;
    }
    int getVal()
    {
        return value;
    }
};

class Array : public SketchContainer
{
public:
    std::vector<Bar *> barList;
    int outer, inner;
    float width, height;
    float x, y;

    int size;
    bool sorted;

    Array(StateManager *applicationStateManager, float x, float y, float width, float height, int size) : SketchContainer(applicationStateManager, x, y, width, height)
    {
        std::cout << "Array Loading" << std::endl;

        this->size = size;
        this->x = x;
        this->y = y;
        this->width = 900 - size * 1;
        this->height = 660;

        reset();
        std::cout << "Array Loaded" << std::endl;
    }

    ~Array()
    {
        for (auto bar : barList)
            delete bar;
    }

    int getOuter() { return outer; }
    int getInner() { return inner; }
    void setOuter(int i) { outer = i; }
    void setInner(int j) { inner = j; }

    void reset()
    {
        if (paused)
        {
            outer = 0;
            inner = 0;
            sorted = false;

            barList.clear();

            for (int i = 0; i < size; i++)
                barList.push_back(new Bar(rand() % 100, size, this->width, this->height));
        }
    }

    void draw()
    {
        int offset = 1;
        temporaryDrawableList.clear();
        for (int i = 0; i < size; i++)
        {
            sf::RectangleShape *rect = new sf::RectangleShape(sf::Vector2f(barList[i]->getWidth(), barList[i]->getHeight()));
            temporaryDrawableList.push_back(rect);

            rect->setPosition(this->x + (2 + barList[i]->getWidth()) * i, this->y + this->height - barList[i]->getHeight());

            if (i == getOuter())
                rect->setFillColor(sf::Color::Green);
            else if (i == getInner())
                rect->setFillColor(sf::Color::Blue);
            else
                rect->setFillColor(barList[i]->getColor());

            rect->setOutlineColor(sf::Color(200, 200, 200, 255));
            rect->setOutlineThickness(1);
        }
    }

    void update()
    {
        draw();
        if (!paused)
            bubbleSort();
        if (sorted)
            paused = true;
    }

    void bubbleSort()
    {

        int i = getOuter();
        int j = getInner();
        std::cout << "Sorting" + i + j << std::endl;

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
};