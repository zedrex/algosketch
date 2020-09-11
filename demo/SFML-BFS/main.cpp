#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

const int maxn = 16;
int visited[maxn][maxn];
int dist[maxn][maxn];
std::pair<int, int> parent[maxn][maxn];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int rows, columns;
float gap, cellWidth, cellHeight;

void init()
{
    memset(visited, 0, sizeof(visited));
    memset(dist, -1, sizeof(dist));
}

void display(sf::RenderWindow &window)
{
    window.clear(sf::Color::Black);
    sf::Font minecraftFont;
    sf::Text cellDistance;
    cellDistance.setPosition(10, 5);
    minecraftFont.loadFromFile("minecraft-font.otf");
    cellDistance.setFont(minecraftFont);
    cellDistance.setFillColor(sf::Color::Black);
    cellDistance.setCharacterSize(cellHeight / 2);

    for (int i = 0; i < maxn; i++)
    {
        for (int j = 0; j < maxn; j++)
        {
            sf::Color silverColor(100, 100, 100);
            sf::RectangleShape cells(sf::Vector2f(cellWidth, cellHeight));
            cells.setPosition((cellWidth + gap) * i, (cellHeight + gap) * j);
            cellDistance.setPosition((cellWidth + gap) * i + 5, (cellHeight + gap) * j + 5);
            if (dist[i][j] == -1)
            {
                cellDistance.setString("inf");
            }
            else
            {
                cellDistance.setString(std::to_string(dist[i][j]));
            }
            if (visited[i][j] == 1)
            {
                cells.setFillColor(silverColor);
            }
            if (visited[i][j] == 2)
            {
                cells.setFillColor(sf::Color::Black);
            }
            if (visited[i][j] == 0)
            {
                cells.setFillColor(sf::Color::White);
            }
            window.draw(cells);
            window.draw(cellDistance);
        }
    }
    window.display();
    sf::sleep(sf::milliseconds(0.1));
}

void bfs(int srcx, int srcy, sf::RenderWindow &window)
{

    std::queue<std::pair<int, int>> q;
    if (srcx >= 0 && srcx < rows && srcy >= 0 && srcy < columns)
    {
        visited[srcx][srcy] = 1;
        dist[srcx][srcy] = 0;
        q.push({srcx, srcy});
    }
    while (!q.empty())
    {
        display(window);
        int px = q.front().first;
        int py = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int x = px + dx[i];
            int y = py + dy[i];
            if (visited[x][y] == 0 && x >= 0 && x < rows && y >= 0 && y < columns)
            {
                dist[x][y] = dist[px][py] + 1;
                visited[x][y] = 1;
                q.push({x, y});
            }
        }
    }
}

int main()
{

    init();
    rows = columns = maxn;
    int screenHeight = 512;
    int screenWidth = 512;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "BFS", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    sf::Clock clock;

    bool start = false;
    int srcx, srcy;
    gap = 2;
    cellWidth = window.getSize().x / (maxn) - (gap + 1);
    cellHeight = window.getSize().y / (maxn) - (gap + 1);

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
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            start = true;
            srcx = mousePosition.x / (cellWidth + gap);
            srcy = mousePosition.y / (cellHeight + gap);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            srcx = mousePosition.x / (cellWidth + gap);
            srcy = mousePosition.y / (cellHeight + gap);
            if (srcx >= 0 and srcx < rows and srcy >= 0 and srcy < columns)
                visited[srcx][srcy] = 2;
            display(window);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            init();
        }
        if (start)
        {
            bfs(srcx, srcy, window);
        }
        start = false;
        display(window);
    }
    return 0;
}