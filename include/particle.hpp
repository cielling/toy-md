#pragma once

#include<vector>

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