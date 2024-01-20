#include<stdio.h>
#include<iostream>
#include<vector>
#include<random>

#include "../include/particle.hpp"

struct params_s {
    const int n_particles = 100;
    const double box_length = 10;
};

int main(int argc, char *argv[]) {

    params_s my_params;
    vector<particle_s> particles;

    std::random_device r_dev;
    std::mt19937 rng(r_dev());
    std::uniform_real_distribution<double> rng_dist(0.0, my_params.box_length);


    // Initialize our particles with random positions and velocities.
    for (int i = 0; i < my_params.n_particles; ++i) {
        particle_s p;
        p.id = i + 1; 
        p.pos[0] = rng_dist(rng);
        p.pos[1] = rng_dist(rng);
        p.pos[2] = rng_dist(rng);
        p.vel[0] = rng_dist(rng);
        p.vel[1] = rng_dist(rng);
        p.vel[2] = rng_dist(rng);
        particles.push_back(p);
    }

    for (auto p: particles) {
        std::cout << "Particle " << p.id << ":" << std::endl;
        std::cout << "x= " << p.pos[0]
                  << " y= " << p.pos[1]
                  << " z= " << p.pos[2];
        std::cout << " vx= " << p.vel[0]
                  << " vy= " << p.vel[1]
                  << " vz= " << p.vel[2] << std::endl;
    }

    return 0;
}