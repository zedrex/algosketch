#pragma once

#include <SFML/Graphics.hpp>
#include <resource.hpp>

class Button
{
public:
    Button(float l_positionX, float l_positionY, float l_sizeX, float l_sizeY, std::string l_buttonText, Resource *l_resource)
    {
        m_shape.setPosition(sf::Vector2f(l_positionX, l_positionY));
        m_shape.setSize(sf::Vector2f(l_sizeX, l_sizeY));
        m_resource = l_resource;

        m_shape.setTexture(m_resource->getIdleButtonTexture());
    }
    ~Button()
    {
    }

    sf::Drawable *getDrawable()
    {
        return &m_shape;
    }

private:
    sf::RectangleShape m_shape;
    Resource *m_resource;
    sf::Text m_text;
};