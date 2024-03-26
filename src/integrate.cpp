#include "../include/integrate.hpp"
#include "../include/interaction.hpp"
#include "../include/particle.hpp"
#include <iostream>
#include <stdexcept>
#include <array>

extern params_s my_params;

void integrate(vector<particle_s> &particles) {
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
            for (int i = 0; i < my_params.n_particles; ++i) {
                particles[i].integrate_reflective(my_params.dt, my_params.box_length);
            }
            break;
        default:
            throw std::invalid_argument("Boundary condition not recognized.");
    };   
}

void update_acc(vector<particle_s> &particles, potential_s &potential) {
    vector<vector<double>> force(my_params.n_particles, vector<double>(3));

    for (int i = 0; i < my_params.n_particles - 1; ++i) {
        for (int j = i + 1; j < my_params.n_particles; ++j) {
            vector<double> f_ij = potential.force(particles[i].pos, particles[j].pos);
            force[i][0] += f_ij[0];
            force[i][1] += f_ij[1];
            force[i][2] += f_ij[2];
            force[j][0] += f_ij[0];
            force[j][1] += f_ij[1];
            force[j][2] += f_ij[2];
        }
    }

    for (int i = 0; i < particles.size(); ++i) {
        particle_s p = particles[i];
        p.acc[0] = force[i][0] / p.mass;
        p.acc[1] = force[i][1] / p.mass;
        p.acc[2] = force[i][2] / p.mass;
        p.vel[0] += p.acc[0] * my_params.dt;
        p.vel[1] += p.acc[1] * my_params.dt;
        p.vel[2] += p.acc[2] * my_params.dt;
    }
}