#include "particle.h"

Particle::Particle(double x, double y, double vx, double vy, double mass, double radius)
    : pos(x, y), vel(vx, vy), mass(mass), force(0, 0), radius(radius) {
    // other initialization code, if needed
}

Vector2D Particle::compute_force(const Particle &other) const {
    Vector2D r = pos - other.pos;
    double distance = r.norm();
    double forceMagnitude = (G * mass * other.mass) / (distance * distance + SOFTENING);
    return r.normalize() * (-forceMagnitude);
}

void Particle::add_force(const Vector2D &new_force) {
    force += new_force;
}

void Particle::update_velocity(double DT) {
    vel += (force / mass) * DT;
    force = Vector2D(0, 0); // Reset force for next iteration
}

void Particle::update_position(double DT) {
    // Update the position based on the current velocity and forces
    pos += vel * DT;

    // Check for collisions with the boundaries, and reverse the velocity component if necessary
    if (pos.x <= 0 || pos.x >= WIDTH) {
        vel.x = -vel.x;
        pos.x = std::fmax(0.0, std::fmin(pos.x, static_cast<double>(WIDTH)));
    }
    if (pos.y <= 0 || pos.y >= HEIGHT) {
        vel.y = -vel.y;
        pos.y = std::fmax(0.0, std::fmin(pos.y, static_cast<double>(HEIGHT)));
    }
}
