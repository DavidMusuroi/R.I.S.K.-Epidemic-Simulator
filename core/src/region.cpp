#include "../include/region.hpp"

Region::Region(const string &name, int population, const string &abbreviation, char **modifiers) : modifiers(modifiers), neighbors(nullptr), nr_neighbors(0), area(name, population, abbreviation), r_rate(0), i_rate(0), m_rate(0){}

void Region::recover(double p){
    area.recover(p);
}

void Region::infect(double p){
    area.infect(p);
}

void Region::kill(double p){
    area.kill(p);
}

void Region::update(const char *modifier){
    if(strcmp(modifier, "starting region") == 0){
        i_rate *= 1.5;
    }
    else if(strcmp(modifier, "dam") == 0){
        i_rate *= 1.05;
        r_rate *= 1.05;
    }
    else if(strcmp(modifier, "mine") == 0){
        i_rate *= 0.95;
        r_rate *= 0.85;
    }
    else if(strcmp(modifier, "mountainous") == 0){
        i_rate *= 0.9;
        r_rate *= 1.2;
    }
    else if(strcmp(modifier, "river") == 0){
        i_rate *= 1.1;
        r_rate *= 0.95;
    }
    else if(strcmp(modifier, "airport") == 0){
        i_rate *= 1.25;
        r_rate *= 0.85;
    }
    else if(strcmp(modifier, "airfield") == 0){
        i_rate *= 1.2;
    }
    else if(strcmp(modifier, "port") == 0){
        i_rate *= 1.15;
        r_rate *= 1.1;
    }
    else if(strcmp(modifier, "capital") == 0){
        i_rate *= 1.5;
        r_rate *= 0.9;
    }
    else if(strcmp(modifier, "end") == 0){
        infect(i_rate);
        recover(r_rate);
        kill(m_rate);
    }
}