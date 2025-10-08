#pragma once
#include "country.hpp"
#include "region.hpp"
#include <string>

using namespace std;

class Simulation{
    private:
        Country **countries;
        Region **regions;
        int nr_modifiers, nr_regions, nr_countries, region_start_index;
        double r_rate, i_rate, m_rate;
    public:
        Simulation();
        void read_countries(const string& path);
        int choose_country(const string& country_name);
        void read_Romania_counties(const string& counties_path, const string& borders_path);
        int choose_county(const string& county_name);
        void update_starting_region(double recovery, double infection, double mortality, int region_start_index);
        void next_day();
        string get_stats(const string& region_name);
        void set_modifier(const string& country_name){
            if(country_name == "Romania"){
                nr_modifiers = 2;
            }
        }
        int get_nr_modifiers(){
            return nr_modifiers;
        }
        int get_nr_regions(){
            return nr_regions;
        }
        int get_nr_countries(){
            return nr_countries;
        }
        int get_region_start_index(){
            return region_start_index;
        }
};