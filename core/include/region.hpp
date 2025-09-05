#pragma once
#include <string>
#include "country.hpp"
using namespace std;

class Region{
    private:
        char **modifiers;
        Country area;

    public:
        Region(const string &name, int population, const string &abbreviation, char **modifiers);

        void recover(int p);
        void infect(int p);
        void kill(int p);

        int get_r() const{
            return area.get_r();
        }
        int get_i() const{
            return area.get_i();
        }
        int get_s() const{
            return area.get_s();
        }
        int get_k() const{
            return area.get_k();
        }
        const string& get_name() const{
            return area.get_name();
        }
        const string& get_abbreviation() const{
            return area.get_abbreviation();
        }
        const char* get_modifier(int i) const{
            return modifiers[i];
        }
};