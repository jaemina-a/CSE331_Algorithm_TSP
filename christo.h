#ifndef CHRISTO_H
#define CHRISTO_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <chrono>
// #include "utils.h"
#include <set>
#include <sstream>
#include <algorithm>

struct Vertex {
    double x,y;
    std::vector<int> connected; //vertex index를 저장하는 벡터
    std::pair<int,int> closeV[2];
};
struct Edge {
    int u, v;
    int weight;
};

class myalgorithm{
private:
    std::vector<Vertex> vertexes;
    int n;
    int cycle_cnt;
    bool answer_exist;
    int optimal_sum;
    std::string file_name;
    std::chrono::microseconds running_time;
    std::vector<std::pair<int, int>> open_node_pairs;  // {u, v} 형태로 저장
    std::vector<int> answer;
    std::vector<int> cycle_couunt_vec;
    std::vector<int> cycle_connect_nodes;
public:
    myalgorithm(std::string file_name,bool answer){
        this->file_name = file_name;
        this->cycle_cnt = 0;
        this->answer_exist = answer;
        read_tsp_file();
        if(answer_exist){
            read_answer_file();
        }
    }
    void read_answer_file();
    void read_tsp_file();
    void cycle_make();
    void cycle_cut();
    void cycle_connect();
    int count_cycle();
    bool has_open_chain();
    void func();
};
class christofied{
private:
    std::vector<int> euler_circuit;

    std::string file_name;
    int n;
    int mst_sum;
    int tsp_sum;
    int optimal_sum;
    bool answer_exist;
    std::chrono::microseconds running_time;
    std::vector<int> answer;
    std::vector<Vertex> vertexes; //all
public:
    christofied(std::string file_name, bool answer_exist){
        this->file_name = file_name;
        this->mst_sum = 0;
        this->tsp_sum = 0;
        this->answer_exist = answer_exist;
        this->optimal_sum = 0;
        read_tsp_file();
        if(answer_exist){
            read_answer_file();
        }
    }
    void read_answer_file();
    void read_tsp_file();
    void MST();
    void perfect_matching();
    void hierholzer();
    void hamilton();
    void tsp(){
        auto start = std::chrono::high_resolution_clock::now();
        MST();
        perfect_matching();
        hierholzer();
        hamilton();
        auto end = std::chrono::high_resolution_clock::now();
        this->running_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
    };
    void print_result(){
        std::cout << "total cost : "<<this->tsp_sum << "\nmst cost : " << this->mst_sum << "\n";
        if(this->answer_exist){
            std::cout <<"optimal cost : " << this->optimal_sum << "\n";
        }
        std::filesystem::path cwd = std::filesystem::current_path();
        
        std::cout << "현재 경로: " << cwd << "\n";
        
        std::string result_file_name = this->file_name + "_Christo"; 
        std::string result_directory = "results/" + result_file_name;
        std::cout << result_directory << std::endl;
        std::ofstream outFile(result_directory);
        outFile << "========================\n";
        outFile << "Total cost : " << this->tsp_sum << "\nMST cost : " << this->mst_sum << "\n";
        if(this->answer_exist){
            outFile << "OPTIMAL COST : " <<this->optimal_sum << "\n";
        }
        outFile << "ACTUAL RUNNING TIME : " << this->running_time.count() << "\n";
        outFile << "========================\n";
        outFile.close();
        
    }
};
#include <sys/resource.h>

static long get_rss_kb() {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return ru.ru_maxrss;          // Linux: kB, macOS: bytes
}

class heldkarp{

private:
    std::string file_name;
    int n;
    int mst_sum;
    int tsp_sum;
    int optimal_sum;
    bool answer_exist;
    std::chrono::microseconds running_time;
    std::vector<int> answer;
    std::vector<Vertex> vertexes; //all
public:
    heldkarp(std::string file_name, bool answer_exist){
        this->file_name = file_name;
        this->answer_exist = answer_exist;
        read_tsp_file();
        if(answer_exist){
            read_answer_file();
        }
    }
    void read_answer_file();
    void held_karp();
    void read_tsp_file();
    void run_heldkapr(){
        
        auto start = std::chrono::high_resolution_clock::now();
        long mem_before = get_rss_kb();
        held_karp();      // 함수 호출
        long mem_after  = get_rss_kb();
        std::cout << "ΔRSS ≃ " << (mem_after - mem_before) << " kB\n";
        auto end = std::chrono::high_resolution_clock::now();
        this->running_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
        // std::cout << this->running_time.count() << std::endl;
    }
    void print_result(){
        std::cout << "total cost : "<<this->tsp_sum << "\n";
        if(this->answer_exist){
            std::cout <<"optimal cost : " << this->optimal_sum << "\n";
        }
        std::string result_file_name = this->file_name + "_Christo"; 
        std::string result_directory = "results/" + result_file_name;
        std::cout << result_directory << std::endl;
        std::ofstream outFile(result_directory);
        outFile << "========================\n";
        outFile << "Total cost : " << this->tsp_sum << "\nMST cost : " << this->mst_sum << "\n";
        if(this->answer_exist){
            outFile << "OPTIMAL COST : " <<this->optimal_sum << "\n";
        }
        outFile << "ACTUAL RUNNING TIME : " << this->running_time.count() << "\n";
        for(int i =0; i<n; i++){
            outFile << answer[i] << "\n";
        }
        outFile << "========================\n";
        outFile.close();
        
    }
};

#endif