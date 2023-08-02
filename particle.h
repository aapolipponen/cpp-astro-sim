#pragma once

#include "Vector2D.h"
#include "constants.h"

class Particle {
public:
    Vector2D pos, vel, force;
    double mass, radius;

    Particle(double x, double y, double vx, double vy, double mass, double radius); // Declaration
    Vector2D compute_force(const Particle &other) const;
    void add_force(const Vector2D &new_force);
    void update_velocity(double dt);
    void update_position(double dt);

    Vector2D get_position() const { return pos; }
    double get_mass() const { return mass; }
    Vector2D get_velocity() const { return vel; }
    double get_radius() const { return radius; }
};
