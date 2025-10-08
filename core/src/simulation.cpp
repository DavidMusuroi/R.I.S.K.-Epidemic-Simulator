#include <exception>
#include "../include/simulation.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <fmt/core.h>

using namespace std;
using namespace fmt;

Simulation::Simulation(): countries(nullptr), regions(nullptr), nr_modifiers(nr_modifiers), nr_regions(0), nr_countries(0),
region_start_index(region_start_index), r_rate(0), i_rate(0), m_rate(0){
    countries = new Country*[2];
    regions = new Region*[43];
}

void Simulation::read_countries(const string& path){
    string name, tmp, abbv, line;
    ifstream csv_countries(path);
    // Header line
    getline(csv_countries, line);
    // Reading the countries from the CSV
    while(getline(csv_countries, line)){
        // Created a stringstream object to separate the columns
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, tmp, ',');
        getline(ss, abbv);
        if (!abbv.empty() && abbv.back() == '\r') {
            abbv.pop_back();
        }
        // Transformed the population to integer and initialized the countries
        int country_population = stoi(tmp);
        countries[nr_countries] = new Country(name, country_population, abbv);
        nr_countries++;
    }
    nr_countries--;
}


int Simulation::choose_country(const string& country_name){
    int country_index = 0;
    for(; country_index <= nr_countries; country_index++){
        if(countries[country_index]->get_name() == country_name){
            break;
        }
    }
    return country_index;
}


void Simulation::read_Romania_counties(const string& counties_path, const string& borders_path){
    string name, tmp, abbv, line;
    int i, county_population;
    ifstream csv_RO_counties(counties_path);
    ifstream csv_RO_borders(borders_path);
    string modifier1, modifier2;
    nr_modifiers = 2;
    // 2 Header lines
    getline(csv_RO_counties, line);
    getline(csv_RO_counties, line);
    // Reading the counties from the CSV
    while(getline(csv_RO_counties, line)){
        char **modifiers = new char*[2];
        // Created a stringstream object to separate the columns
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, abbv, ',');
        getline(ss, tmp, ',');
        getline(ss, modifier1, ',');
        getline(ss, modifier2);
        if (!modifier2.empty() && modifier2.back() == '\r') {
            modifier2.pop_back();
        }
        // Transformed the population to integer and stored modifiers correctly, as well as initialized the counties
        county_population = stoi(tmp);
        modifiers[0] = strdup(modifier1.c_str());
        modifiers[1] = strdup(modifier2.c_str());
        regions[nr_regions] = new Region(name, county_population, abbv, modifiers);
        nr_regions++;
        }

        nr_regions--;
        getline(csv_RO_borders, line);


        // Reading the neighbors from the CSV
        while(getline(csv_RO_borders, line)){
            stringstream ss(line);
            getline(ss, tmp, ' ');
            for(i = 0; i <= nr_regions; i++){
                if(regions[i]->get_abbreviation() == tmp){
                    break;
                }
            }
            while(getline(ss, tmp, ' ')){
                if (!tmp.empty() && tmp.back() == '\r') {
                    tmp.pop_back();
                }
                    regions[i]->set_neighbor(tmp.c_str());
            }
        }
}

int Simulation::choose_county(const string& county_name){
    int region_start_index = 0;
    for(; region_start_index <= nr_regions; region_start_index++){
        if(regions[region_start_index]->get_name() == county_name){
            break;
        }
    }
    return region_start_index;
}

void Simulation::update_starting_region(double recovery, double infection, double mortality, int region_start_index){
    r_rate = recovery;
    i_rate = infection;
    m_rate = mortality;
    regions[region_start_index]->set_i_rate(i_rate);
    regions[region_start_index]->set_r_rate(r_rate);
    regions[region_start_index]->set_m_rate(m_rate);
    regions[region_start_index]->update("starting region");
    for(int i = 0; i < nr_modifiers; i++){
        regions[region_start_index]->update(regions[region_start_index]->get_modifier(i));
    }
    regions[region_start_index]->update("end");
}

void Simulation::next_day(){
    int i, j, index;
    double buffer[nr_regions + 1] = {0};
    while(true){
        for(i = 0; i <= nr_regions; i++){
            if(regions[i]->get_i() != 0){
                int nr_neighbors = regions[i]->get_nr_neighbors();
                for(j = 0; j < nr_neighbors; j++){
                    string tmp = regions[i]->get_neighbor(j);
                    for(index = 0; index <= nr_regions; index++){
                        if(tmp == regions[index]->get_abbreviation()){
                                break;
                        }
                    }
                    buffer[index] += (double) (regions[i]->get_i_rate() / nr_neighbors);
                }
            }
        }

        for(i = 0; i <= nr_regions; i++){
            if(buffer[i] > 0){
                regions[i]->add_i_rate(buffer[i]);
                regions[i]->add_r_rate(buffer[i] * 4 / 10);
                regions[i]->add_m_rate(buffer[i] * 3 / 5);
                buffer[i] = 0;
            }
            for(j = 0; j < nr_modifiers; j++){
                regions[i]->update(regions[i]->get_modifier(j));
            }
            regions[i]->update("end");
        }
    }
}

string Simulation::get_stats(const string& region_name){
    for(int i = 0; i <= nr_regions; i++){
        if(region_name == regions[i]->get_abbreviation()){
            return format("Stats :\nR : {}\nI : {}\nS : {}\nK : {}\nInfection rate : {}\n", regions[i]->get_r(), regions[i]->get_i(), regions[i]->get_s(), regions[i]->get_k(), regions[i]->get_i_rate());
        }
    }
    return "No region of this name found!";
}