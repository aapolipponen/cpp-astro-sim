#include "Vector2D.h"

Vector2D::Vector2D(double x, double y) : x(x), y(y) { }

double Vector2D::norm() const {
    return std::sqrt(x * x + y * y);
}

double Vector2D::squaredNorm() const {
    return x * x + y * y;
}

Vector2D Vector2D::normalize() const {
    double magnitude = norm();
    return Vector2D(x / magnitude, y / magnitude);
}

Vector2D Vector2D::operator+(const Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(double scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(double scalar) const {
    return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D &other) {
    x += other.x;
    y += other.y;
    return *this;
}
