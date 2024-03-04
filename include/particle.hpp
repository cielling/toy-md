#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "params.hpp"

using std::vector;

enum class ParticleType {
    NONE,
    OTHER // TODO: update later with real types
};


struct particle_s {
    vector<double> pos{0, 0, 0};
    vector<double> vel{0, 0, 0};
    vector<double> acc{0, 0, 0};
    double mass = -1.0;

    ParticleType ptype = ParticleType::NONE;
    long id = -1;

    void integrate(const double dt) {
        pos[0] += vel[0] * dt + acc[0] * dt * dt;
        pos[1] += vel[1] * dt + acc[1] * dt * dt;
        pos[2] += vel[2] * dt + acc[2] * dt * dt;
    }

    void integrate_periodic(const double dt, const double box_length) {
        pos[0] = fmod((pos[0] + vel[0] * dt + acc[0] * dt * dt), box_length);
        pos[1] = fmod((pos[1] + vel[1] * dt + acc[1] * dt * dt), box_length);
        pos[2] = fmod((pos[2] + vel[2] * dt + acc[2] * dt * dt), box_length);
    }

    void integrate_reflective(const double dt, const double box_length) {
        pos[0] = (pos[0] + vel[0] * dt + acc[0] * dt * dt);
        pos[1] = (pos[1] + vel[1] * dt + acc[1] * dt * dt);
        pos[2] = (pos[2] + vel[2] * dt + acc[2] * dt * dt);
        /* Reflect off lower boundary. */
        if (pos[0] < 0.0) {
            pos[0] = -pos[0];
            vel[0] = fabs(vel[0]);
        }
        if (pos[1] < 0.0) {
            pos[1] = -pos[1];
            vel[1] = fabs(vel[1]);
        }
        if (pos[2] < 0.0) {
            pos[2] = -pos[2];
            vel[2] = fabs(vel[2]);
        }
        /* Reflect off upper boundary. */
        if (pos[0] > box_length) {
            pos[0] = 2 * box_length - pos[0];
            vel[0] = -fabs(vel[0]);
        }
        if (pos[1] > box_length) {
            pos[1] = 2 * box_length - pos[1];
            vel[1] = -fabs(vel[1]);
        }
        if (pos[2] > box_length) {
            pos[2] = 2 * box_length - pos[2];
            vel[2] = -fabs(vel[2]);
        }
    }

    void print() {
        std::cout << "Particle " << id << ":" << std::endl;
        std::cout << "x= " << pos[0]
                  << " y= " << pos[1]
                  << " z= " << pos[2];
        std::cout << " vx= " << vel[0]
                  << " vy= " << vel[1]
                  << " vz= " << vel[2] << std::endl;
    }
};

void init_particles(vector<particle_s> &particles);

void print_particles(const vector<particle_s> &particles);

void write_particles(const vector<particle_s> &particles, const std::string filename, const int iter);

void write_particles_ovito(const vector<particle_s> particles, const std::string file_base, const int iter);