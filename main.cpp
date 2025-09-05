#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <fmt/core.h>
#include "core/include/country.hpp"

using namespace std;
using namespace fmt;

int main(){
    /**
    string name;
    int population;
    print("Enter the country name: ");
    getline(cin, name);
    print("Enter the number of people living here: ");
    cin >> population;
    Country c(name, population);
    print("The country's name is {}, and has a total of {} people\n", c.get_name(), c.get_s());
    **/
    string name, line, choice, tmp;
    int population, nr_countries = 0, i;
    Country **countries = new Country*[2];
    bool okay = false;
    ifstream csv_file("../data/countries.csv");
    // Header line
    getline(csv_file, line);
    print("The countries you can choose from are:\n");
    // While we can read from the csv
    while(getline(csv_file, line)){
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
        print("Enter which country you would like to choose from\n");
        getline(cin, choice);
        for(i = 0; i < nr_countries && okay == false; i++){
            if(countries[i]->get_name() == choice){
                okay = true;
            }
        }
        if(okay == false){
            print("ERR! Incorect Country!\n");
        }
    }
    i--;
    print("You went for {}\n", countries[i]->get_name());
}