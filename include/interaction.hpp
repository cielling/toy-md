#pragma once
#include <vector>
#include <math.h>

using std::vector;

struct potential_s {
    virtual double potential(const vector<double> &pos1, const vector<double> &pos2) = 0;
    virtual vector<double> force(const vector<double> &pos1, const vector<double> &pos2) = 0;
};

struct LJpotential_s : potential_s {
    double eps = 30682.0;
    double sigma = 2.928;
    double sigma6 = sigma * sigma * sigma * sigma * sigma * sigma;
    double sigma12 = sigma6 * sigma6;
    double r_min = std::pow(2.0, 1./6.) * sigma;

    double potential(const vector<double> &pos1, const vector<double> &pos2) {
        vector<double> r = {0.0, 0.0, 0.0};
        r[0] = pos1[0] - pos2[0];
        r[1] = pos1[1] - pos2[1];
        r[2] = pos1[2] - pos2[2];
        double r2 = r[0] * r[0] + r[1] * r[1] + r[2] * r[2];
        double r6 = sigma6 / (r2 * r2 * r2);
        double r12 = r6 * r6;
        double potential = 4.0 * eps * (r12 - r6);
        return potential;
    }

    vector<double> force(const vector<double> &pos1, const vector<double> &pos2) {
        vector<double> r = {0.0, 0.0, 0.0};
        r[0] = pos1[0] - pos2[0];
        r[1] = pos1[1] - pos2[1];
        r[2] = pos1[2] - pos2[2];
        double r2 = r[0] * r[0] + r[1] * r[1] + r[2] * r[2];
        double r_mag = std::sqrt(r2);
        double r8 = sigma6 / (r2 * r2 * r2 * r2);
        double r14 = 2.0 * sigma12 / (r2 * r2 * r2 * r2 * r2 * r2 * r2);
        double force = 24.0 * eps * (r14 - r8);
        vector<double> force_vec = {
            force * r[0] / r_mag,
            force * r[1] / r_mag,
            force * r[2] / r_mag
        };
        force_vec.push_back(force);
        return force_vec;
    }
};
