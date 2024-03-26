#pragma once

#include <iostream>
#include <string>

#include "../extern/cxxopts/include/cxxopts.hpp"

enum class BoundaryType : int {
    NONE,
    PERIODIC,
    REFLECTIVE
};

static const std::string name_boundary_type[] = {
    "None",
    "Periodic",
    "Reflective"
};

static const std::map<BoundaryType, std::string> map_boundary_type = {
    {BoundaryType::NONE, "None"},
    {BoundaryType::PERIODIC, "Periodic"},
    {BoundaryType::REFLECTIVE, "Reflective"}
};

template<typename K, typename V>
static std::map<V, K> reverse_map(const std::map<K, V>& m) {
    std::map<V, K> r;
    for (const auto& kv : m)
        r[kv.second] = kv.first;
    return r;
}

static std::map<std::string, BoundaryType> rmap_boundary_type = reverse_map(map_boundary_type);

/* If I don't have this and try to print a BoundaryType value directly, I get a compile error
 * that it doesn't know how to print a BoundaryType value. If I do have this, the linker complains
 * that this is already defined in main. 
 * Fix this once I know more C++. */
// std::ostream& operator<< (std::ostream& out, const BoundaryType value) {
//     const std::string name_boundary_type[] = {
//         "None",
//         "Periodic",
//         "Reflective"
//     };

//     return out << name_boundary_type[static_cast<std::underlying_type<BoundaryType>::type>(value)];
// }

struct params_s {
    int n_particles = 100;
    int n_iter = 50;
    double box_length = 100;
    double dt = 0.1;
    BoundaryType boundary_type = BoundaryType::PERIODIC;
    std::string last_restart_file;// = "..\\test\\snake_eyes.csv";

    void set_params(int argc, char *argv[]) {

        cxxopts::Options options("md");
        
        options.add_options()
        ("n,number", "Number of particles", cxxopts::value<int>()->default_value("100")) 
        ("L,length", "Box length", cxxopts::value<double>()->default_value("100.0"))
        ("i,iteration", "Number of iterations", cxxopts::value<int>()->default_value("50"))
        ("t,timestep", "Size of time step", cxxopts::value<double>()->default_value("0.1"))
        ("b,boundary", "boundary type: N(ONE), P(ERIODIC), R(EFLECTIVE)", cxxopts::value<char>()->default_value("P"))
        ("f,file", "Dump file to (re-)start from", cxxopts::value<std::string>()->default_value(""));

        options.parse_positional({"input_files"});
        cxxopts::ParseResult result;

        result = options.parse(argc, argv);

        if (result.count("number")) n_particles = result["number"].as<int>();

        if (result.count("length")) box_length = result["length"].as<double>();

        if (result.count("iteration")) n_iter = result["iteration"].as<int>();
        
        if (result.count("timestep")) dt = result["timestep"].as<double>();

        if (result.count("boundary")) {
            switch (result["boundary"].as<char>()) {
                case 'N':
                    boundary_type = BoundaryType::NONE;
                    break;
                case 'P':
                    boundary_type = BoundaryType::PERIODIC;
                    break;
                case 'R':
                    boundary_type = BoundaryType::REFLECTIVE;
                    break;
                default:
                    boundary_type = BoundaryType::NONE;
                    std::cout << "Unrecognized boundary type. Using 'NONE'.";
            };
        }

        if (result.count("file")) last_restart_file = result["file"].as<std::string>();
    }

    void print() {
        std::cout << "Parameters of this simulation:\n";
        std::cout << "Number of particles: " << n_particles << std::endl;
        std::cout << "Number of iterations: " << n_iter << std::endl;
        std::cout << "Box length: " << box_length << std::endl;
        std::cout << "Boundary type: " << name_boundary_type[static_cast<std::underlying_type<BoundaryType>::type>(boundary_type)] << std::endl;
        std::cout << "Time step: " << dt << std::endl;
        std::cout << "(Re-)start file: " << last_restart_file << std::endl;
    }
};