#include "../include/country.hpp"
#include "../include/region.hpp"
#include "../include/simulation.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;

PYBIND11_MODULE(RISK_pycore, m){
    m.doc() = "Python bind";

    pybind11::class_<Country>(m, "Country")
        .def(pybind11::init<const string&, int, const string&>())
        .def("get_name", &Country::get_name)
        .def("get_abbreviation", &Country::get_abbreviation);

    pybind11::class_<Region>(m, "Region")
        .def(pybind11::init([](const string& name, int population, const string& abbr, pybind11::list tmp){
            int n = pybind11::len(tmp);
            char **modifiers = new char*[n];
            for(int i = 0; i < n; i++){
                string s = pybind11::cast<string>(tmp[i]);
                modifiers[i] = strdup(s.c_str());
            }
            return new Region(name, population, abbr, modifiers);
        }));

    pybind11::class_<Simulation>(m, "Simulation")
        .def(pybind11::init<>())
        .def("read_countries", &Simulation::read_countries)
        .def("choose_country", &Simulation::choose_country)
        .def("read_Romania_counties", &Simulation::read_Romania_counties)
        .def("choose_county", &Simulation::choose_county)
        .def("set_modifier", &Simulation::set_modifier)
        .def("update_starting_region", &Simulation::update_starting_region)
        .def("next_day", &Simulation::next_day)
        .def("get_stats", &Simulation::get_stats)
        .def("get_nr_modifiers", &Simulation::get_nr_modifiers)
        .def("get_nr_regions", &Simulation::get_nr_regions)
        .def("get_nr_countries", &Simulation::get_nr_countries)
        .def("get_region_start_index", &Simulation::get_region_start_index);
}