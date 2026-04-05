#include "../includes/Graph.hpp"

Graph::Graph(const unsigned int size) : _size(size) {

}

Graph::~Graph() {
	_vec.clear();
}

void Graph::addVector(const Vector2& vec) {
    const std::pair<const float, const float> pair = vec.getPoints();
    if (isPointPresent(pair)) {
        std::cout << "Graph::addVector -> " << vec << ": Duplicate vector !" << std::endl;
        return;
    }
    else if ((pair.first > _size) || (pair.second > _size) || (pair.first < 0) || (pair.second < 0)) {
        std::cout << "Graph::addVector -> " << vec << ": Out Of Bounds points !" << std::endl;
    }
    _vec.push_back(vec);
}

void Graph::addVector(const float x, const float y) {
    const std::pair<const float, const float> pair = std::make_pair(x,y);
    if (isPointPresent(pair)) {
        std::cout << "Graph::addVector -> " << pair.first << '/' << pair.second << ": Duplicate vector !" << std::endl;
        return;
    } else if ((pair.first > _size) || (pair.second > _size) || (pair.first < 0) || (pair.second < 0)) {
        std::cout << "Graph::addVector -> " << pair.first << '/' << pair.second << ": Out Of Bounds points !" << std::endl;
    }
    _vec.push_back(Vector2(x, y));
}

bool Graph::isPointPresent(const std::pair<const float, const float>& point) {
    for (std::vector<Vector2>::iterator it = _vec.begin() ; it != _vec.end(); it++) {
        if (it->getPoints() == point) {
            return (true);
        }
    }
    return (false);
}

void Graph::display() {
    for (int row(_size + 1); row >= 0; row--) {
        if ((row) >= 1) {
            std::cout << row - 1 << ' ';
        }
        for (int col(0); col <= 5; col++) {
            if ((col - 1) == -1 && row == 0) {
                std::cout << "  ";
            } 
            if (row == 0) {
                std::cout << col << "  ";
            }
            else {
                if (isPointPresent(std::make_pair(row-1, col))) {
                    std::cout << "X  ";
                } else {
                    std::cout << ".  ";
                }
            }
        }
        std::cout << std::endl;
    }
}
