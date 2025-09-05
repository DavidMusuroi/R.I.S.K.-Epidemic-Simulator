#include "../include/region.hpp"

Region::Region(const string &name, int population, const string &abbreviation, char **modifiers) : modifiers(modifiers), area(name, population, abbreviation){}

void Region::recover(int p){
    area.recover(p);
}

void Region::infect(int p){
    area.infect(p);
}

void Region::kill(int p){
    area.kill(p);
}