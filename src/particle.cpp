#include "../include/particle.hpp"
#include "../include/params.hpp"
#include<stdio.h>
#include <string>
#include<iostream>
#include<vector>
#include<random>
#include<fstream>
#include<iomanip>

extern params_s my_params;

using std::string;

void init_random_particles(vector<particle_s> &particles) {
    std::random_device r_dev;
    std::mt19937 rng(r_dev());
    std::uniform_real_distribution<double> rng_dist(0.0, my_params.box_length);


    // Initialize our particles with random positions and velocities.
    for (int i = 0; i < my_params.n_particles; ++i) {
        particle_s p;
        p.id = i + 1; 
        p.pos[0] = rng_dist(rng);
        p.pos[1] = rng_dist(rng);
        p.pos[2] = rng_dist(rng);
        p.vel[0] = rng_dist(rng);
        p.vel[1] = rng_dist(rng);
        p.vel[2] = rng_dist(rng);
        p.mass = 1.0;
        particles.push_back(p);
    }
}

int load_particles(vector<particle_s> & particles, string const & filename) {
    std::fstream f_in;
    f_in.open(filename, std::ios::in);
    std::ios_base::iostate err_state = f_in.rdstate();
    if (!f_in) {
        std::cout << "Error opening (re-)start file! Exiting..." << std::endl;
        std::perror("Error: ");
        exit(1);
    }

    if (!f_in.is_open()) {
        std::cout << "Error: file is not open! Exiting..." << std::endl;
        exit(1);
    }

    vector<string> row, header;
    vector<vector<string>> all_rows;
    string line, word, word2, temp, t;

    std::cout << "Reading file" << std::endl;

    while (getline(f_in, line)) {
        header.clear();
        // getline(f_in, line);
        std::cout << line << std::endl;
        std::stringstream s(line);
        std::getline(s, word, ',');
        std::getline(s, word2, ',');
        std::cout << "word, word2: " << word << ", " << word2 << std::endl;
        if (word.compare("n_particles") == 0) my_params.n_particles = std::stoi(word2);
        if (word.compare("box_length") == 0) my_params.box_length = std::stoi(word2);
        if (word.compare("last_dt") == 0) my_params.dt = std::stod(word2);
        if (word.compare("boundary_type") == 0) my_params.boundary_type = rmap_boundary_type[word2];
        if (word.compare("id") == 0) break;
    }

    std::cout << "New parameters for this simulation:" << std::endl;
    my_params.print();

    int count = 0;

    all_rows.clear();
    while (std::getline(f_in, line)) {
        ++count;
        // std::getline(f_in, line);
        // split line on comma
        std::stringstream s(line);
        row.clear();
        while (std::getline(s, word, ',')) {
                row.push_back(word);
        };
        all_rows.push_back(row);
    }

    f_in.close();

    for (auto r : all_rows) {
        particle_s p;
        p.id = std::stoi(r[0]); 
        p.ptype = static_cast<ParticleType>(std::stoi(r[1]));
        p.pos[0] = std::stod(r[3]);
        p.pos[1] = std::stod(r[4]);
        p.pos[2] = std::stod(r[5]);
        p.vel[0] = std::stod(r[6]);
        p.vel[1] = std::stod(r[7]);
        p.vel[2] = std::stod(r[8]);
        p.acc[0] = std::stod(r[9]);
        p.acc[1] = std::stod(r[10]);
        p.acc[2] = std::stod(r[11]);
        p.mass = std::stod(r[12]);
        particles.push_back(p);
    }

    if (count != my_params.n_particles)
        std::cout << "WARNING: number of particles in file is inconsistent with n_particles!\n";
    
    return count;
}

void print_particles(const vector<particle_s> &particles) {
    for (auto p: particles) {
        p.print();
    }
}

void write_particles(const vector<particle_s> &particles, const string file_base, const int iter) {
    std::ofstream my_file;
    string file_name = file_base + "-" + std::to_string(iter) + ".csv";
    my_file.open(file_name, std::ios::out);
    // write data
    my_file << std::setw(15) << std::setprecision(8);
    my_file << "id,x,y,z,vx,vy,vz" << std::endl;
    for (auto p: particles) {
        my_file << p.id << ","
                << p.mass << ","
                << p.pos[0] << ","
                << p.pos[1] << ","
                << p.pos[2] << ","
                << p.vel[0] << ","
                << p.vel[1] << ","
                << p.vel[2] << ","
                << p.acc[0] << ","
                << p.acc[1] << ","
                << p.acc[2] << ","
                << std::endl;
    }
    my_file.close();
}

void write_particles_ovito(const vector<particle_s> particles, const string file_base, const int iter) {
    std::ofstream my_file;
    string file_name = file_base + "-" + std::to_string(iter) + ".dump";
    my_file.open(file_name, std::ios::out);
    // write data
    my_file << "ITEM: TIMESTEP" << std::endl;
    my_file << iter << std::endl;
    my_file << "ITEM: NUMBER OF ATOMS" << std::endl;
    my_file << my_params.n_particles << std:: endl;
    my_file << "ITEM: BOX BOUNDS pp pp pp" << std::endl;
    my_file << "0 " << my_params.box_length << std::endl;
    my_file << "0 " << my_params.box_length << std::endl;
    my_file << "0 " << my_params.box_length << std::endl;
    my_file << "ITEM: ATOMS id mol type x y z" << std::endl;
    for (auto p: particles) {
        my_file << p.id << " "
                << 0 << " "
                << static_cast<int>(p.ptype) << " "
                << p.pos[0] << " "
                << p.pos[1] << " "
                << p.pos[2]
                << std::endl;
    }
    my_file.close();
}