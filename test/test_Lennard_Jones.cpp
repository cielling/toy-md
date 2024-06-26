#include <iostream>
#include <vector>
#include <math.h>

#include "../include/interaction.hpp"

#include "../extern/googletest/googletest/include/gtest/gtest.h"

namespace {

TEST(Lennard_Jones, potential_r_min) {
    LJpotential_s lj;
    vector<double> p1 = {0.0, 1.0, lj.r_min};
    vector<double> p2 = {0.0, 1.0, 0.0};
    double potential_mag = 4.0 * lj.eps * (std::pow(lj.sigma / lj.r_min, 12.0) - std::pow(lj.sigma / lj.r_min, 6.0));
    double potential = lj.potential(p1, p2);
    EXPECT_FLOAT_EQ(potential_mag, potential);
}

TEST(Lennard_Jones, potential_r_1) {
    LJpotential_s lj;
    vector<double> p1 = {0.0, 1.0, 1.0};
    vector<double> p2 = {0.0, 2.0, 1.0};
    double potential_mag = 4.0 * lj.eps * (std::pow(lj.sigma / 1.0, 12.0) - std::pow(lj.sigma / 1.0, 6.0));
    double potential = lj.potential(p1, p2);
    EXPECT_FLOAT_EQ(potential_mag, potential);
}

TEST(Lennard_Jones, potential_r_4) {
    LJpotential_s lj;
    vector<double> p1 = {0.0, 1.0, 0.0};
    vector<double> p2 = {4.0, 1.0, 0.0};
    double potential_mag = 4.0 * lj.eps * (std::pow(lj.sigma / 4.0, 12.0) - std::pow(lj.sigma / 4.0, 6.0));
    double potential = lj.potential(p1, p2);
    EXPECT_FLOAT_EQ(potential_mag, potential);
}

TEST(Lennard_Jones, force_r_min) {
    LJpotential_s lj;
    vector<double> p1 = {0.0, 1.0, lj.r_min};
    vector<double> p2 = {0.0, 1.0, 0.0};
    double force_mag = 24.0 * lj.eps * (2.0 * lj.sigma12 / std::pow(lj.r_min, 14.0) - lj.sigma6 / std::pow(lj.r_min, 8.0));
    vector<double> force_actual = {0.0, 0.0, force_mag, force_mag};
    vector<double> force = lj.force(p1, p2);
    EXPECT_FLOAT_EQ(force_actual[0], force[0]);
    EXPECT_FLOAT_EQ(force_actual[1], force[1]);
    EXPECT_FLOAT_EQ(force_actual[2], force[2]);
    EXPECT_FLOAT_EQ(force_actual[3], force[3]);
}

TEST(Lennard_Jones, force_r_1) {
    LJpotential_s lj;
    vector<double> p1 = {0.0, 1.0, 1.0};
    vector<double> p2 = {0.0, 2.0, 1.0};
    double force_mag = 24.0 * lj.eps * (2.0 * lj.sigma12 / std::pow(1.0, 14.0) - lj.sigma6 / std::pow(1.0, 8.0));
    vector<double> force_actual = {0.0, -force_mag, 0.0, force_mag};
    vector<double> force = lj.force(p1, p2);
    EXPECT_FLOAT_EQ(force_actual[0], force[0]);
    EXPECT_FLOAT_EQ(force_actual[1], force[1]);
    EXPECT_FLOAT_EQ(force_actual[2], force[2]);
    EXPECT_FLOAT_EQ(force_actual[3], force[3]);
}

TEST(Lennard_Jones, force_r_4) {
    LJpotential_s lj;
    vector<double> p1 = {0.0, 1.0, 0.0};
    vector<double> p2 = {4.0, 1.0, 0.0};
    double force_mag = 24.0 * lj.eps * (2.0 * lj.sigma12 / std::pow(4.0, 14.0) - lj.sigma6 / std::pow(4.0, 8.0));
    vector<double> force_actual = {-force_mag, 0.0, 0.0, force_mag};
    vector<double> force = lj.force(p1, p2);
    EXPECT_FLOAT_EQ(force_actual[0], force[0]);
    EXPECT_FLOAT_EQ(force_actual[1], force[1]);
    EXPECT_FLOAT_EQ(force_actual[2], force[2]);
    EXPECT_FLOAT_EQ(force_actual[3], force[3]);
}

}