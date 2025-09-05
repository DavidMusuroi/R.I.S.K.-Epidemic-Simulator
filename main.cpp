#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <fmt/core.h>
#include "core/include/country.hpp"

using namespace std;
using namespace fmt;

int main(){
    string name, line, choice, tmp;
    int population, nr_countries = 0, i;
    Country **countries = new Country*[2];
    bool okay = false;
    ifstream csv_countries("../data/countries.csv");
    ifstream csv_RO_counties("../data/RO_counties.csv");
    // Header line
    getline(csv_countries, line);
    print("The countries you can choose from are:\n");
    // While we can read from the csv
    while(getline(csv_countries, line)){
        // Create a stringstream object to separate the columns
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, tmp, ',');
        // Transform the population to integer and initialize the countries
        population = stoi(tmp);
        countries[nr_countries] = new Country(name, population);
        print("{}\n", countries[nr_countries]->get_name());
        nr_countries++;
    }
    while(okay == false){
        print("Enter which country you would like to play as:\n");
        getline(cin, choice);
        for(i = 0; i < nr_countries && okay == false; i++){
            if(countries[i]->get_name() == choice){
                okay = true;
            }
        }
        if(okay == false){
            print("ERROR! Incorect Country! The countries you can choose from are:\n");
            for(i = 0; i < nr_countries; i++){
                print("{}\n", countries[i]->get_name());
            }
        }
    }
    i--;
    print("You went for {}\n", countries[i]->get_name());
    
}