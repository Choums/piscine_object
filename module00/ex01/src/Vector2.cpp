#include "../includes/Vector2.hpp"


Vector2::Vector2(const float x, const float y) : _point(std::make_pair(fabsf(x), fabsf(y))) {
}

std::pair<const float, const float> Vector2::getPoints() const {
    return (this->_point);
}
