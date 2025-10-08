#include "simulation.hpp"
#include <iostream>

int main(){
    Simulation sim;
    sim.read_countries("../data/countries.csv");
    sim.choose_country("Romania");
    sim.read_Romania_counties("../data/RO_counties.csv", "../data/RO_borders.csv");
    return 0;
}