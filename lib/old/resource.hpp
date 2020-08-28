#pragma once

#include <SFML/Graphics.hpp>

class Resource
{
public:
    Resource()
    {
        buttonTexture.loadFromFile("assets/images/button.png");
    }

    sf::Texture *getIdleButtonTexture()
    {
        return &buttonTexture;
    }
    sf::Texture buttonTexture;
};