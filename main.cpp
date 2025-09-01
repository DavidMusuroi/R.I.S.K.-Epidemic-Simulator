#include <iostream>
#include <string>
#include <fmt/core.h>
#include "core/include/country.hpp"

using namespace std;
using namespace fmt;

int main(){
    string name;
    int population;
    print("Enter the country name: ");
    getline(cin, name);
    print("Enter the number of people living here: ");
    cin >> population;
    Country c(name, population);
    print("The country's name is {}, and has a total of {} people\n", c.get_name(), c.get_s());
}