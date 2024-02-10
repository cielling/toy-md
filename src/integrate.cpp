#include "../include/integrate.hpp"
#include <iostream>
#include <stdexcept>

void integrate(vector<particle_s> &particles, const params_s my_params) {
    switch(my_params.boundary_type) {
        case BoundaryType::NONE:
            for (int i = 0; i < my_params.n_particles; ++i) {
                particles[i].integrate(my_params.dt);
            }
            break;
        case BoundaryType::PERIODIC:
            for (int i = 0; i < my_params.n_particles; ++i) {
                particles[i].integrate_periodic(my_params.dt, my_params.box_length);
            }
            break;
        case BoundaryType::REFLECTIVE:
            throw std::invalid_argument("Boundary condition 'REFLECTIVE' is not implemented yet.");
            break;
        default:
            throw std::invalid_argument("Boundary condition not recognized.");
    };
    
}