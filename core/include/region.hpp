#pragma once
#include <string>
#include "country.hpp"
#include <cstring>
using namespace std;

class Region{
    private:
        char **modifiers, **neighbors;
        int nr_neighbors;
        Country area;
        double r_rate, i_rate, m_rate;

    public:
        Region(const string &name, int population, const string &abbreviation, char **modifiers);

        void recover(double p);
        void infect(double p);
        void kill(double p);
        void update(const char *modifier);

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
        double get_i_rate() const{
            return i_rate;
        }
        double get_r_rate() const{
            return r_rate;
        }
        double get_m_rate() const{
            return m_rate;
        }
        void set_i_rate(double new_i_rate){
            i_rate = new_i_rate;
        }
        void set_r_rate(double new_r_rate){
            r_rate = new_r_rate;
        }
        void set_m_rate(double new_m_rate){
            m_rate = new_m_rate;
        }
        void add_i_rate(double old_i_rate){
            i_rate += old_i_rate;
        }
        void add_r_rate(double old_r_rate){
            r_rate += old_r_rate;
        }
        void add_m_rate(double old_m_rate){
            m_rate += old_m_rate;
        }
        void set_neighbor(const char *neighbor){
            if(neighbors == NULL){
                neighbors = new char*[10];
                nr_neighbors = 0;
                for(int i = 0; i < 10; i++){
                    neighbors[i] = new char[4];
                }
            }
            strcpy(neighbors[nr_neighbors], neighbor);
            nr_neighbors++;
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
        const char* get_neighbor(int i) const{
            return neighbors[i];
        }
        int get_nr_neighbors() const{
            return nr_neighbors;
        }
};