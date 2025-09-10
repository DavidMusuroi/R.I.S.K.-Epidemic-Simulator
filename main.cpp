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
    int country_population, nr_countries = 0, country_index, region_index, nr_modifiers, nr_regions = 0, i, j;
    double i_rate, r_rate, m_rate, tmp_i_rate, tmp_r_rate, tmp_m_rate;
    Country **countries = new Country*[2];
    bool okay = false, stop = false;
    ifstream csv_countries("../data/countries.csv");
    ifstream csv_RO_counties("../data/RO_counties.csv");
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
        Region **regions = new Region*[42];
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
                print("{}, ", regions[nr_regions]->get_name());
                nr_regions++;
            }
            else{
                print("{}\n", regions[nr_regions]->get_name());
            }
        }

        okay = false;

        //Choosing your county
        while(okay == false){
            print("Enter which county you would like to start as:\n");
            getline(cin, choice);
            for(region_index = 0; region_index <= nr_regions && okay == false; region_index++){
                if(regions[region_index]->get_name() == choice){
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
        region_index--;
        print("You went for {}, which has the abbreviation {}, the index {}, and the modifiers: {} and {}\n", regions[region_index]->get_name(), regions[region_index]->get_abbreviation(), region_index, regions[region_index]->get_modifier(0), regions[region_index]->get_modifier(1));
        print("What initial percentages would you like the infection, recovery and mortality rates to be?\n");
        cin >> i_rate >> r_rate >> m_rate;
        getline(cin, choice);
        print("{} {} {} Alright, let the simulation begin!\n", i_rate, r_rate, m_rate);
        regions[region_index]->set_i_rate(i_rate);
        regions[region_index]->set_r_rate(r_rate);
        regions[region_index]->set_m_rate(m_rate);
        while(stop == false){
            stop = true;
            print("Would you like to continue (C) or quit (Q) the simulation? ");
            getline(cin, choice);
            while(choice != "C" && choice != "Q"){
                print("ERROR! Incorrect input!\n");
                getline(cin, choice);
            }
            if(choice == "C"){
                stop = false;
            }
            else if(choice == "Q"){
                break;
            }
            regions[region_index]->update(i_rate, r_rate, m_rate, "starting region");
            for(j = 0; j < nr_modifiers; j++){
                    regions[region_index]->update(i_rate, r_rate, m_rate, regions[region_index]->get_modifier(j));
            }
            regions[region_index]->update(i_rate, r_rate, m_rate, "end");
            i_rate = regions[region_index]->get_i_rate();
            r_rate = regions[region_index]->get_r_rate();
            m_rate = regions[region_index]->get_m_rate();
            print("Would you like to see the stats for your starting region? (Y) or (N) : ");
            getline(cin, choice);
            print("\n");
            if(choice == "Y"){
                print("R.I.S.K. results :\n{} {} {} {}\n", regions[region_index]->get_r(), regions[region_index]->get_i(), regions[region_index]->get_s(), regions[region_index]->get_k());
            }
            else if(choice == "N"){
                print("Alright, let's continue.\n");
            }
            else{
                print("ERROR! Unknown character!\n");
            }
        }
    }
}