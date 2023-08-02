#pragma once
#include <cmath>

class Vector2D {
public:
    double x, y;
    Vector2D(double x = 0, double y = 0);
    double norm() const;
    Vector2D normalize() const;
    Vector2D operator+(const Vector2D &other) const;
    Vector2D operator-(const Vector2D &other) const;
    Vector2D operator*(double scalar) const;
    Vector2D operator/(double scalar) const; // Division by scalar
    Vector2D& operator+=(const Vector2D &other);
};
