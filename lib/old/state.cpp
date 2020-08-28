#include <state.hpp>

State::State(Resource *l_resource)
{
    m_resource = l_resource;

    Label *topLabel = new Label(10, 10, 1180, 50);
    Label *visualizationLabel = new Label(10, 70, 900, 660);
    Label *inputLabel = new Label(920, 70, 270, 660);

    Button *inputButton = new Button(10, 740, 50, 300, "Run", m_resource);
    m_labels.push_back(topLabel);
    m_labels.push_back(visualizationLabel);
    m_labels.push_back(inputLabel);
}

State::~State()
{
    for (auto label : m_labels)
        delete label;

    for (auto button : m_buttons)
        delete button;
}

void State::draw(sf::RenderTarget *l_window)
{
    for (auto label : m_labels)
        l_window->draw(*label->getDrawable());

    for (auto button : m_buttons)
        l_window->draw(*button->getDrawable());
}