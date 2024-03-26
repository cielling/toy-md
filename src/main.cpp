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

    // for (int i = 0; i < argc; ++i) {
    //     std::cout << argv[i] << std::endl;
    // }

    my_params.set_params(argc, argv);

    my_params.print();

    if (!my_params.last_restart_file.empty()) {
        load_particles(particles, my_params.last_restart_file);
    } else {
        init_random_particles(particles);
    }

    LJpotential_s LennardJones;

    //print_particles(particles);

    // Write initial particle positions
    write_particles_ovito(particles, "..\\output\\my_particles", 0);

    for (int i = 1; i < my_params.n_iter + 1; ++i) {
        update_acc(particles, LennardJones);
        integrate(particles);
        write_particles_ovito(particles, "..\\output\\my_particles", i);
    }

    return 0;
}