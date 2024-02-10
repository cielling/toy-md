#include "../include/integrate.hpp"
#include <iostream>

void integrate(vector<particle_s> &particles, const params_s my_params) {
    for (int i = 0; i < my_params.n_particles; ++i) {
        particles[i].integrate(my_params.dt);
    }
}