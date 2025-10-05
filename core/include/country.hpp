#pragma once
#include <string>
using namespace std;

class Country{
    private:
        const string name, abbreviation;
        int r, i, s, k;

    public:
        Country(const string &name, int population, const string &abbreviation);

        void recover(double p);
        void infect(double p);
        void kill(double p);

        int get_r() const{
            return r;
        }
        int get_i() const{
            return i;
        }
        int get_s() const{
            return s;
        }
        int get_k() const{
            return k;
        }
        const string& get_name() const{
            return name;
        }
        const string& get_abbreviation() const{
            return abbreviation;
        }
};