#include<stdio.h>
#include<iostream>
#include<vector>
#include<random>

#include "../include/particle.hpp"


int main(int argc, char *argv[]) {

    params_s my_params;
    vector<particle_s> particles;

    init_particles(particles, my_params);

    print_particles(particles);

    write_particles(particles, "my_particles", 0);

    return 0;
}