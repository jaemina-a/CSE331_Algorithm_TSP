#include "christo.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <utility>
#include <chrono>
#include <string>

int main() {
    std::vector<std::pair<std::string, bool>> test_cases={
        // std::pair<std::string, bool>("a280", true),
        // std::pair<std::string, bool>("ulysses16", true),
        std::pair<std::string, bool>("a280_short", false),
        // std::pair<std::string, bool>("xql662", true),
        // std::pair<std::string, bool>("kz9976", true),
        // std::pair<std::string, bool>("mona-lisa100K", false)
    };
    for(int i=0 ;i<test_cases.size(); i++){
        std::string file_name = test_cases[i].first;
        heldkarp myh(file_name, false);
        myh.run_heldkapr();
        // myh.print_result();
        // christofied my_christo(file_name,test_cases[i].second);
        // myalgorithm my_algo(file_name, test_cases[i].second);
        // my_christo.tsp();
        // my_christo.print_result();
        // my_algo.func();
    }
    return 0;
}

