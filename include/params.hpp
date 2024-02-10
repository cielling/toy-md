#pragma once

enum class BoundaryType {
    NONE,
    PERIODIC,
    REFLECTIVE
};
struct params_s {
    const int n_particles = 100;
    const int n_iter = 20;
    const double box_length = 100;
    const double dt = 0.1;
    const BoundaryType boundary_type = BoundaryType::PERIODIC;
};