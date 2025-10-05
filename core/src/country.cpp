#include "../include/country.hpp"

Country::Country(const string &name, int population, const string &abbreviation) : name(name), abbreviation(abbreviation), r(0), i(0), k(0){
    s = population;
}

void Country::recover(double p){
    int total = i * p / 100;
    if(total > i){
        total = i;
    }
    i -= total;
    r += total;
}

void Country::infect(double p){
    int total = s * p / 100;
    if(total > s){
        total = s;
    }
    s -= total;
    i += total;
}

void Country::kill(double p){
    int total = i * p / 100;
    if(total > i){
        total = i;
    }
    i -= total;
    k += total;
}