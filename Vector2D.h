#pragma once
#include <cmath>

class Vector2D {
public:
    double x, y;
    Vector2D(double x = 0, double y = 0);
    double norm() const;
    double squaredNorm() const; // New method to return the squared magnitude of the vector
    Vector2D normalize() const; // Method to return a normalized version of the vector
    Vector2D operator+(const Vector2D &other) const; // Overload of the addition operator
    Vector2D operator-(const Vector2D &other) const; // Overload of the subtraction operator
    Vector2D operator*(double scalar) const; // Overload of the multiplication by scalar operator
    Vector2D operator/(double scalar) const; // Overload of the division by scalar operator
    Vector2D& operator+=(const Vector2D &other); // Overload of the addition assignment operator
};
