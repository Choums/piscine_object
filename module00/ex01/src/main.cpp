#include <iostream>
#include "../includes/Graph.hpp"
#include "../includes/Vector2.hpp"

int main()
{
    Graph* graph = new Graph();
    Vector2* vec1 = new Vector2(2.0f, 2.0f);
    graph->addVector(*vec1);
    graph->addVector(2.0f, 2.0f);
    graph->addVector(1.0f, 2.0f);
    graph->addVector(3.0f, 2.0f);
    graph->addVector(5.0f, 5.0f);
    graph->addVector(-1.0f, 5.0f);
    graph->addVector(0, 0);
    graph->addVector(0, 1);
    graph->addVector(0, 2);
    graph->addVector(0, 3);
    graph->addVector(0, 4);
    graph->addVector(0, 5);
    
    graph->display();
    return (0);
}