#pragma once
#include<vector>
#include"params.hpp"
#include"particle.hpp"
#include "interaction.hpp"

void integrate(vector<particle_s> &particles);

void update_acc(vector<particle_s> &particles, potential_s &potential);