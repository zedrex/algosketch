#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace algo
{
    class Array
    {
    public:
        // update(); Figure out how to update state on tick
        // draw(// Rectangular area of whose dimension will be the base of the drawing);

        // selectionSort(); Use command design pattern?

    private:
        std::vector<sf::RectangleShape> array;
    };
} // namespace algo