#pragma once

#include <iostream>
#include <cmath>

class Vector2 {
    public:
        Vector2(const float x = 0.0f, const float y = 0.0f);
        ~Vector2() = default;

        std::pair<const float, const float> getPoints() const;

    private:
        std::pair<const float, const float> _point;

    public:
        friend std::ostream& operator<<(std::ostream& p_os, const Vector2& p_vector)
		{
            const float x = p_vector.getPoints().first;
            const float y = p_vector.getPoints().second;
            p_os << x << '/' << y << std::endl;
            
			return (p_os);
		}
};