#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WIDTH = 800; // Your window's width
const int HEIGHT = 800; // Your window's height

const bool BOUNDARY_COLLISIONS = true; // Collision for the corners of the window so that they don't escape the seen area
const double DT = 2; // Timestep
const int N_BODIES = 5000; // Amount of bodies
const double G = 6.67430e-11; // Gravitational constant
const double SOFTENING = 0; // Softening factor to prevent division by zero
const int iterations = 5000;

const double SIMULATION_SIZE_CM = 10.0; // Size of your simulation in centimeters
const double SCALE_FACTOR = SIMULATION_SIZE_CM / WIDTH; // Number of centimeters per pixel

extern const double radius_cm;
extern double radius_pixels;

#endif // CONSTANTS_H
