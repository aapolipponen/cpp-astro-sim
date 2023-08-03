#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include "particle.h"
#include "constants.h"

int main() {
    const double radius_cm = 0.05;
    double radius_pixels = radius_cm / SCALE_FACTOR;

    // Open a file for writing
    std::ofstream file("data.txt");

    std::vector<Particle> particles;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> pos_dist(-SIMULATION_SIZE_CM/2, SIMULATION_SIZE_CM/2); // for positions within 10cm
    std::uniform_real_distribution<> vel_dist(-0.01, 0.01); // for velocities
    std::uniform_real_distribution<> mass_dist(1.0, 10.0); // for masses
    std::uniform_real_distribution<> radius_dist(radius_cm, radius_cm); // for radii

    // Initialize particles with random positions, velocities, masses, and radii
    for (int i = 0; i < N_BODIES; i++) {
        double x = pos_dist(gen) * SCALE_FACTOR; // convert from cm to pixels
        double y = pos_dist(gen) * SCALE_FACTOR; // convert from cm to pixels
        double vx = vel_dist(gen);
        double vy = vel_dist(gen);
        double mass = mass_dist(gen);
        double radius = radius_dist(gen) * SCALE_FACTOR; // convert from cm to pixels
        std::string name = "Body " + std::to_string(i);
        particles.push_back(Particle(x, y, vx, vy, mass, radius, name));
    }

    for (int iter = 0; iter < iterations; iter++) {
        std::cout << "Iteration: " << iter << ", Number of Particles: " << particles.size() << "\n"; // Debugging print

        // Compute gravitational forces, print them, and save them to a file.
        for (int i = 0; i < particles.size(); i++) {
            Particle &p = particles[i];
            Vector2D position = p.get_position();
            double mass = p.get_mass(); // Assuming a get_mass() method in Particle class
            double radius = p.get_radius(); // Assuming a get_radius() method in Particle class

            // Print to console
            std::cout << p.get_name() << ": Position: (" << position.x << ", " << position.y
                      << "), Mass: " << mass << ", Radius: " << radius << "\n";

            // Save to file
            file << p.get_name() << ": Position: (" << position.x << ", " << position.y
                 << "), Mass: " << mass << ", Radius: " << radius << "\n";

            int x = static_cast<int>(position.x * 400 + 400);
            int y = static_cast<int>(position.y * 300 + 300);
        }

        // Update velocities and positions
        for (auto &p : particles) {
            p.update_velocity(DT);
            p.update_position(DT);
        }

        // Collision handling
        for (int i = 0; i < particles.size(); i++) {
            for (int j = i + 1; j < particles.size(); j++) {
                double distance = (particles[i].get_position() - particles[j].get_position()).norm();
                double threshold = particles[i].get_radius() + particles[j].get_radius();
                if (distance < threshold) {
                    // Compute total momentum and kinetic energy before collision
                    Vector2D totalMomentum = particles[i].get_velocity() * particles[i].get_mass() + particles[j].get_velocity() * particles[j].get_mass();
                    double totalEnergy = 0.5 * particles[i].get_mass() * particles[i].get_velocity().squaredNorm() +
                                         0.5 * particles[j].get_mass() * particles[j].get_velocity().squaredNorm();

                    // Compute new mass and radius
                    double combinedMass = particles[i].get_mass() + particles[j].get_mass();
                    double combinedRadius = pow(pow(particles[i].get_radius(), 3) + pow(particles[j].get_radius(), 3), 1.0/3.0); // Assuming spheres

                    // Compute new position
                    Vector2D combinedPosition = (particles[i].get_position() * particles[i].get_mass() + particles[j].get_position() * particles[j].get_mass()) / combinedMass;

                    // Calculate lost energy (e.g. 10% loss) and calculate total energy after collision
                    double energyLoss = 0.1 * totalEnergy; // 10% energy loss
                    double totalEnergyAfter = totalEnergy - energyLoss;

                    // Calculate the new velocity from momentum conservation and new total energy
                    Vector2D combinedVelocity = totalMomentum / combinedMass; // velocity from momentum conservation
                    double newVelocityMagnitude = sqrt(2 * totalEnergyAfter / combinedMass); // velocity from energy conservation
                    combinedVelocity = combinedVelocity.normalize() * newVelocityMagnitude; // assign the new magnitude to the velocity, keeping the direction

                    // Create new particle
                    Particle combinedParticle(combinedPosition.x, combinedPosition.y, combinedVelocity.x, combinedVelocity.y, combinedMass, combinedRadius, "Combined Body");

                    // Replace particles[i] with the combined particle
                    particles[i] = combinedParticle;

                    // Remove particles[j]
                    particles.erase(particles.begin() + j);

                    // Decrement j to ensure no skipping over the next particle
                    j--;
                }
            }
        }

        for (auto &p : particles) {
            int x = static_cast<int>(p.get_position().x * 400 + 400);
            int y = static_cast<int>(p.get_position().y * 300 + 300);
        }

    } // End of iterations loop

    // Close the file
    file.close();

    return 0;
}