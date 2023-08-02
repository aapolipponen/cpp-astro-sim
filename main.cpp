#include <SDL.h>
#include <vector>
#include <random>
#include "particle.h"
#include "constants.h"

int main() {

    std::vector<Particle> particles;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> pos_dist(-1.0, 1.0); // for positions
    std::uniform_real_distribution<> vel_dist(-0.01, 0.01); // for velocities
    std::uniform_real_distribution<> mass_dist(1.0, 10.0); // for masses
    std::uniform_real_distribution<> radius_dist(5.0, 15.0); // for radii

    // Initialize particles with random positions, velocities, masses, and radii
    for (int i = 0; i < N_BODIES; i++) {
        double x = pos_dist(gen);
        double y = pos_dist(gen);
        double vx = vel_dist(gen);
        double vy = vel_dist(gen);
        double mass = mass_dist(gen);
        double radius = radius_dist(gen);
        particles.push_back(Particle(x, y, vx, vy, mass, radius));
    }

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create an SDL window
    SDL_Window *window = SDL_CreateWindow("Particle Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Main simulation loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Compute gravitational forces
        for (auto &p1 : particles) {
            for (auto &p2 : particles) {
                if (&p1 != &p2) {
                    Vector2D force = p1.compute_force(p2);
                    p1.add_force(force);
                }
            }
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
                    // Implement inelastic collision logic here...
                }
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render each particle as a point (or circle depending on the radius)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        for (auto &p : particles) {
            int x = static_cast<int>(p.get_position().x * 400 + 400);
            int y = static_cast<int>(p.get_position().y * 300 + 300);
            // You can use SDL_RenderDrawPoint if you want to draw them as points, or another function if you want to draw them as circles
            SDL_RenderDrawPoint(renderer, x, y);
        }

        // Display the particles
        SDL_RenderPresent(renderer);
    }

    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
