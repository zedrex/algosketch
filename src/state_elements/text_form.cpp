#include<state_elements/text_form.hpp>
#include<sstream>

TextForm::TextForm(StateManager *applicationStateManager, float x, float y, float width, float height, int fontSize, sf::Color color) : StateElement(applicationStateManager, x, y, width, height)
{
    this->text->setString("");
    this->text->setFont(globalFont);
    this->text->setFillColor(sf::Color::Black);
    this->text->setCharacterSize(fontSize);

    this->shape->setFillColor(color);

    this->keyboardInput = "";
}

TextForm::~TextForm()
{
}

void TextForm::update()
{
    leftAlignTextOnShape();

    //Check text input
    std::string currentText = this->getTextInput();

    if (currentText == "\b")
    {
        if (this->keyboardInput.size() != 1)
            this->keyboardInput = this->keyboardInput.substr(0, this->keyboardInput.size() - 1);
    }
    else if (currentText == "\r")
    {
        this->keyboardInput += "\n";
    }
    else
    {
        this->keyboardInput += currentText;

        // Text wrap (Spaghetti version)
        size_t textSize = this->keyboardInput.size();
        if (textSize % 18 == 0 and this->keyboardInput[textSize - 1] != '\n')
            this->keyboardInput += "\n";
    }

    //Finalize the text string
    this->text->setString(this->keyboardInput + "_");
}

std::string TextForm::getText()
{
    return this->keyboardInput;
}

// Extract integers from the text
std::vector<int> TextForm::extractValues()
{
    std::vector<int> integers;
    std::stringstream textStream;
    std::string streamWord;
    int extractedInteger;

    textStream << this->getText();

    while (!textStream.eof())
    {
        // Load each word into a string
        textStream >> streamWord;
        // Convert to integer and push it to the vector
        if (std::stringstream(streamWord) >> extractedInteger)
            integers.push_back(extractedInteger);
    }
    return integers;
}