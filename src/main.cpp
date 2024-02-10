#include<stdio.h>
#include<iostream>
#include<vector>
#include<random>

#include "../include/particle.hpp"
#include "../include/integrate.hpp"

int main(int argc, char *argv[]) {

    params_s my_params;
    vector<particle_s> particles;

    init_particles(particles, my_params);

    //print_particles(particles);

    // Write initial particle positions
    write_particles(particles, "my_particles", 0);

    for (int i = 1; i < my_params.n_iter + 1; ++i) {
        integrate(particles, my_params);
        write_particles_ovito(particles, my_params, "my_particles", i);
    }

    return 0;
}