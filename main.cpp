#include "tsp.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <utility>
#include <chrono>
#include <string>

int main() {
    std::vector<std::pair<std::string, bool>> test_cases={
        std::pair<std::string, bool>("a280", true),
        // std::pair<std::string, bool>("ulysses16", true),
        // std::pair<std::string, bool>("a280_short", false),
        std::pair<std::string, bool>("xql662", true),
        // std::pair<std::string, bool>("kz9976", true),
        // std::pair<std::string, bool>("mona-lisa100K", false)
    };
    /*
        클래스 정의후
        run_tsp -> 알고리즘 동작
        make_result_file -> txt파일로 만들기
    */
    for(int i=0 ;i<test_cases.size(); i++){
        std::string file_name = test_cases[i].first;
        /*held karp*/
        // heldkarp myh(file_name, false);
        // myh.run_heldkapr();
        // myh.print_result();
        
        /*christofied*/
        christofied my_christo(file_name,test_cases[i].second);
        my_christo.run_tsp();
        my_christo.make_result_file();
        
        /*myalgorithm*/
        // myalgorithm my_algo(file_name, test_cases[i].second);
        // my_algo.run_tsp();
        // my_algo.make_result_file();
    }
    return 0;
}

