#pragma once

#include<vector>
#include<string>
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

    ParticleType ptype = ParticleType::NONE;
    long id = -1;
};

void init_particles(vector<particle_s> &particles, const params_s my_params);

void print_particles(const vector<particle_s> &particles);

void write_particles(const vector<particle_s> &particles, const std::string filename, const int iter);