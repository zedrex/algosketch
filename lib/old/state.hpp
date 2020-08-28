#pragma once

#include <SFML/Graphics.hpp>
#include <window.hpp>
#include <button.hpp>
#include <resource.hpp>

class Label
{
public:
    Label(float l_positionX, float l_positionY, float l_sizeX, float l_sizeY)
    {
        m_position = sf::Vector2f(l_positionX, l_positionY);
        m_size = sf::Vector2f(l_sizeX, l_sizeY);
        m_area.setPosition(m_position);
        m_area.setSize(m_size);
        m_area.setFillColor(sf::Color(200, 200, 200, 200));
    }

    ~Label()
    {
    }

    sf::Drawable *getDrawable()
    {
        return &m_area;
    }

private:
    sf::RectangleShape m_area;
    sf::Vector2f m_size;
    sf::Vector2f m_position;
};

class State
{
public:
    State();
    State(Resource *l_resource);
    ~State();

    void draw(sf::RenderTarget *l_window);

private:
    Resource *m_resource;
    std::vector<Label *> m_labels;
    std::vector<Button *> m_buttons;
};
