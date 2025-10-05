#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <fmt/core.h>
#include "core/include/country.hpp"
#include "core/include/region.hpp"

using namespace std;
using namespace fmt;

int main(){
    string name, line, choice, tmp, abbv;
    int country_population, nr_countries = 0, country_index, region_start_index, nr_modifiers, nr_regions = 0, i, j, index, k;
    double i_rate, r_rate, m_rate;
    Country **countries = new Country*[2];
    bool okay = false;
    ifstream csv_countries("../data/countries.csv");
    ifstream csv_RO_counties("../data/RO_counties.csv");
    ifstream csv_RO_borders("../data/RO_borders.csv");
    // Header line
    getline(csv_countries, line);
    print("The countries you can choose from are:\n");


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
        country_population = stoi(tmp);
        countries[nr_countries] = new Country(name, country_population, abbv);
        print("{}\n", countries[nr_countries]->get_name());
        nr_countries++;
    }

    nr_countries--;


    // Choosing your country
    while(okay == false){
        print("Enter which country you would like to play as:\n");
        getline(cin, choice);
        for(country_index = 0; country_index <= nr_countries && okay == false; country_index++){
            if(countries[country_index]->get_name() == choice){
                okay = true;
            }
        }
        if(okay == false){
            print("ERROR! Incorect country! The countries you can choose from are:\n");
            for(i = 0; i <= nr_countries; i++){
                print("{}\n", countries[i]->get_name());
            }
        }
    }

    country_index--;
    print("You went for {}, which has the abbreviation {} and the index {}\n", countries[country_index]->get_name(), countries[country_index]->get_abbreviation(), country_index);



    if(countries[country_index]->get_name() == "Romania"){
        int county_population;
        Region **regions = new Region*[43];
        string modifier1, modifier2;
        nr_modifiers = 2;
        // 2 Header lines
        getline(csv_RO_counties, line);
        getline(csv_RO_counties, line);
        print("The counties you can choose from are:\n");


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
            if(nr_regions != 41){
                print("{}\n", regions[nr_regions]->get_name());
                nr_regions++;
            }
            else{
                print("{}\n", regions[nr_regions]->get_name());
            }
        }


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


        okay = false;


        //Choosing your county
        while(okay == false){
            print("Enter which county you would like to start as:\n");
            getline(cin, choice);
            for(region_start_index = 0; region_start_index <= nr_regions && okay == false; region_start_index++){
                if(regions[region_start_index]->get_name() == choice){
                    okay = true;
                }
            }
            if(okay == false){
                print("ERROR! Incorect county! The counties you can choose from are:\n");
                for(i = 0; i <= nr_regions; i++){
                    print("{}\n", regions[i]->get_name());
                }
            }
        }
        region_start_index--;


        print("\nYou went for {}, which has the abbreviation {}, the index {}, and the modifiers: {} and {}\n", regions[region_start_index]->get_name(), regions[region_start_index]->get_abbreviation(), region_start_index, regions[region_start_index]->get_modifier(0), regions[region_start_index]->get_modifier(1));
        print("What initial percentages would you like the infection, recovery and mortality rates to be?\n");
        cin >> i_rate >> r_rate >> m_rate;
        regions[region_start_index]->set_i_rate(i_rate);
        regions[region_start_index]->set_r_rate(r_rate);
        regions[region_start_index]->set_m_rate(m_rate);
        regions[region_start_index]->update("starting region");
        for(i = 0; i < nr_modifiers; i++){
            regions[region_start_index]->update(regions[region_start_index]->get_modifier(i));
        }
        regions[region_start_index]->update("end");
        getline(cin, choice);
        print("\nAlright, let the simulation begin!\n");

        double buffer[nr_regions + 1] = {0};

        okay = false;

        while(true){
            for(i = 0; i <= nr_regions; i++){
                if(regions[i]->get_i() != 0){
                    int nr_neighbors = regions[i]->get_nr_neighbors();
                    for(j = 0; j < nr_neighbors; j++){
                        tmp = regions[i]->get_neighbor(j);
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
                    regions[i]->add_m_rate(buffer[i] * 6 / 10);
                    buffer[i] = 0;
                }
                for(j = 0; j < nr_modifiers; j++){
                    regions[i]->update(regions[i]->get_modifier(j));
                }
                regions[i]->update("end");
            }

            print("Would you like to see the stats for any region? (Y) or (N) : ");
            getline(cin, choice);
            while(choice != "Y" && choice != "N"){
                print("ERROR! Unknown character! Choose between yes (Y) or no (N).\n");
                getline(cin, choice);
            }
            if(choice == "Y"){
                print("Write the region for which you would like to see the stats : ");
                while(okay == false){
                    getline(cin, choice);
                    for(i = 0; i <= nr_regions; i++){
                        if(choice == regions[i]->get_name()){
                            okay = true;
                            break;
                        }
                    }
                    if(okay == false){
                        print("Error! Incorrect region!\n");
                    }
                }
                okay = false;
                print("R.I.S.K. results :\n{} {} {} {} {}\n\n", regions[i]->get_r(), regions[i]->get_i(), regions[i]->get_s(), regions[i]->get_k(), regions[i]->get_i_rate());
            }
            else if(choice == "N"){
                print("Alright, let's continue.\n\n");
            }

            print("Would you like to continue (C) or quit (Q) the simulation? ");
            getline(cin, choice);
            while(choice != "C" && choice != "Q"){
                print("ERROR! Incorrect input! You must choose to continue (C) or quit (Q) the simulation.\n");
                getline(cin, choice);
            }
            if(choice == "Q"){
                print("Simulation ended!\n");
                break;
            }
        }
    }
}