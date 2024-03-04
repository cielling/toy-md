#include<stdio.h>
#include<iostream>
#include<vector>
#include<random>

#include "../include/particle.hpp"
#include "../include/integrate.hpp"
#include "../include/interaction.hpp"

params_s my_params;

int main(int argc, char *argv[]) {

    vector<particle_s> particles;

    my_params.set_params(argc, argv);

    my_params.print();

    init_particles(particles);

    LJpotential_s LennardJones;

    //print_particles(particles);

    // Write initial particle positions
    write_particles(particles, "my_particles", 0);

    for (int i = 1; i < my_params.n_iter + 1; ++i) {
        integrate(particles);
        update_acc(particles, LennardJones);
        write_particles_ovito(particles, "my_particles", i);
    }

    return 0;
}