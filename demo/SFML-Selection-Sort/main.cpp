#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

int main()
{
    int listSize = 32;

    int screenHeight = 768;
    int screenWidth = 1024;

    int fontSize = 20;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Selection Sort", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    window.setFramerateLimit(60);
    sf::Clock clock;
    sf::Font minecraftFont;
    sf::Text sortStatus, swapStatus, arrayStatus;
    sortStatus.setPosition(10, 5);

    minecraftFont.loadFromFile("minecraft-font.otf");

    sortStatus.setFont(minecraftFont);
    swapStatus.setFont(minecraftFont);
    arrayStatus.setFont(minecraftFont);

    sortStatus.setFillColor(sf::Color::Black);
    swapStatus.setFillColor(sf::Color::Black);
    arrayStatus.setFillColor(sf::Color::Black);

    sortStatus.setCharacterSize(fontSize);
    swapStatus.setCharacterSize(fontSize);
    arrayStatus.setCharacterSize(fontSize);

    bool sorted = false;
    bool paused = true;
    bool sorting = false;
    int sortSpeed = 40;
    int arrayAccess = 0;

    std::vector<int> list;

    for (int i = 1; i <= listSize; i++)
    {
        list.push_back(i);
    }
    std::random_shuffle(list.begin(), list.end());

    int gap = 2;
    float barWidth = window.getSize().x / (listSize)-gap;
    float barHeight = (window.getSize().y - 50) / (listSize)-gap;

    int i = 0, j = i + 1, minimumIndex = i;
    std::string status, swapStatusString = "", arrayStatusString = "Array -> 0";

    // Game loop
    while (window.isOpen())
    {
        sf::Event ev1;
        while (window.pollEvent(ev1))
        {
            if (ev1.type == sf::Event::Closed)
            {
                std::cout << "Closing window" << std::endl;
                window.close();
            }

            else if (ev1.type == sf::Event::Resized)
            {
                std::cout << "Window size: " << ev1.size.width << " " << ev1.size.height << std::endl;
            }

            else if (ev1.type == sf::Event::KeyPressed)
            {
                if (ev1.key.code == sf::Keyboard::S)
                {
                    if (paused)
                    {
                        arrayAccess = 0;
                        swapStatusString = "";
                        std::random_shuffle(list.begin(), list.end());
                        sorted = false;
                        sorting = false;
                    }
                }
                else if (ev1.key.code == sf::Keyboard::Space)
                {
                    if (paused)
                        paused = false;
                    else
                        paused = true;
                    sorting = true;
                }
                else if (ev1.key.code == sf::Keyboard::Equal)
                {
                    if (sortSpeed > 10)
                        sortSpeed -= 10;
                }
                else if (ev1.key.code == sf::Keyboard::Dash)
                {
                    if (sortSpeed < 200)
                        sortSpeed += 10;
                }
            }
        }

        //SORTING
        if (!sorting)
        {
            i = 0, j = i + 1, minimumIndex = i;
            swapStatusString = "";
        }

        if (i < listSize and !paused)
        {
            if (j < listSize)
            {
                sf::sleep(sf::milliseconds(sortSpeed));
                if (list[j] < list[minimumIndex])
                {
                    minimumIndex = j;
                }
                arrayAccess++;
                j++;
            }
            if (j == listSize)
            {
                std::swap(list[i], list[minimumIndex]);
                swapStatusString = "swapped " + std::to_string(i) + " and " + std::to_string(minimumIndex);
                i++;
                minimumIndex = i;
                j = i + 1;
            }
        }

        //Show
        if (std::is_sorted(list.begin(), list.end()))
        {
            sorted = true;
            paused = true;
            sorting = false;
        }
        else
        {
            sorted = false;
        }
        window.clear(sf::Color::White);
        if (!sorted and sorting)
        {
            status = "sorting for index " + std::to_string(i);
        }
        else if (!sorting and !sorted)
        {
            status = "unsorted";
        }
        else if (sorted)
        {
            status = "sorted";
        }
        arrayStatusString = "Array access -> " + std::to_string(arrayAccess);

        sortStatus.setString(status);
        swapStatus.setString(swapStatusString);
        arrayStatus.setString(arrayStatusString);

        swapStatus.setPosition(screenWidth - swapStatusString.size() * (3 * fontSize / 4), 5);
        arrayStatus.setPosition(10, 2 * fontSize);

        window.draw(sortStatus);
        window.draw(swapStatus);
        window.draw(arrayStatus);
        for (int k = 0; k < listSize; k++)
        {
            sf::RectangleShape bars(sf::Vector2f(barWidth, -barHeight * list[k]));
            if ((k == i or k == j or k == minimumIndex) and !sorted and sorting)
            {
                if (k == i)
                    bars.setFillColor(sf::Color::Red);
                if (k == j)
                    bars.setFillColor(sf::Color::Blue);
                if (k == minimumIndex)
                    bars.setFillColor(sf::Color::Green);
            }
            else
            {
                bars.setFillColor(sf::Color::Black);
            }
            bars.setPosition((barWidth + gap) * k, screenHeight - gap);
            window.draw(bars);
        }
        window.display();
    }

    return 0;
}