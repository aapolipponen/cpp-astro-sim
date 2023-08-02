#ifndef CONSTANTS_H
#define CONSTANTS_H

const bool BOUNDARY_COLLISIONS = true; // Collision for the corners of the window so that they don't escape the seen area
const double DT = 1; // Timestep
const int N_BODIES = 1000; // Amount of bodies
const double G = 6.67430e-11; // Gravitational constant
const double SOFTENING = 1e-9; // Softening factor to prevent division by zero

const int WIDTH = 800; // Your window's width
const int HEIGHT = 800; // Your window's height

#endif // CONSTANTS_H
