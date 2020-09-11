#include<state_elements/state_element.hpp>

class TextForm : public StateElement
{
public:
    TextForm(StateManager *applicationStateManager, float x, float y, float width, float height, int fontSize, sf::Color color);
    ~TextForm();

    void update();
    std::string getText();
    std::vector<int> extractValues();

private:
    std::string keyboardInput;
};