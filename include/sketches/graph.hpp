#pragma once

#include <SFML/Graphics.hpp>
#include <state_elements/state_element.hpp>
#include <sketches/sketch_container.hpp>

class Node : public StateElement
{
public:
    Node(StateManager *applicationStateManager, int value, float x, float y, float radius, float sketchWidth, float sketchHeight);
    ~Node();
    float getRadius();

    void setColor(sf::Color newColor);
    sf::Color getColor();

    void setPosition(sf::Vector2i newPosition);
    sf::Vector2f getPosition();
    sf::CircleShape *getNodeShape();
    sf::Vector2i sendMousePosition();
    sf::Vector2f getCenter();
    void update();

private:
    int value;
    float radius;
    float areaHeight, areaWidth;
    float x, y;

    sf::CircleShape nodeShape;
    sf::Text nodeIndexText;
    sf::Color nodeColor;
};

class Edge
{
public:
    Edge(Node *firstNode, Node *secondNode);
    ~Edge();
    void setColor(sf::Color newColor);
    void update();
    float getNewAngle(sf::Vector2f firstPoint, sf::Vector2f secondPoint);
    float getNewLength(sf::Vector2f firstPoint, sf::Vector2f secondPoint);
    sf::RectangleShape *getEdgeShape();

private:
    float areaHeight, areaWidth;
    float edgeWidth, edgeLength, edgeAngle;

    Node *firstNode;
    Node *secondNode;
    sf::Color color;
    sf::RectangleShape edgeShape;
};

class Graph : public SketchContainer
{
public:
    Graph(StateManager *applicationStateManager, float x, float y, float width, float height, int size, Action action);
    ~Graph();

    std::vector<Node *> nodeList;
    std::vector<Edge *> edgeList;

    float graphWidth, graphHeight;
    float nodeRadius, edgeWidth;
    int numberOfNodes, numberOfEdges;

    float x, y;
    Action action;
    int size;
    bool completed;

    void reset();
    void draw();
    void update();

    void depthFirstSearch();
    void breadthFirstSearch();
    void dijkstra();
};