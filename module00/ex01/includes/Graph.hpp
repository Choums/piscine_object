#pragma once

#include <iostream> 
#include <vector> 
#include "../includes/Vector2.hpp"

class Vector2;

class Graph {
    public:
        Graph(const unsigned int size = 5U);
        ~Graph();

        void addVector(const Vector2& vec);
        void addVector(const float x, const float y);

        void display();
    private:
        bool isPointPresent(const std::pair<const float, const float>& point);

        unsigned int _size;
        std::vector<Vector2> _vec;
};