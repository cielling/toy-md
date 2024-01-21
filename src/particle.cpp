#include "../include/particle.hpp"
#include "../include/params.hpp"
#include<stdio.h>
#include<iostream>
#include<vector>
#include<random>

void init_particles(vector<particle_s> &particles, const params_s my_params) {
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
}

void print_particles(const vector<particle_s> &particles) {
    for (auto p: particles) {
        std::cout << "Particle " << p.id << ":" << std::endl;
        std::cout << "x= " << p.pos[0]
                  << " y= " << p.pos[1]
                  << " z= " << p.pos[2];
        std::cout << " vx= " << p.vel[0]
                  << " vy= " << p.vel[1]
                  << " vz= " << p.vel[2] << std::endl;
    }
}