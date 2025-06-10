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

struct Vertex
{
    double x, y;
    std::vector<int> connected; // vertex index를 저장하는 벡터
    std::pair<int, int> closeV[2];
};
struct Edge
{
    int u, v;
    int weight;
};

class tsp
{
protected:
    std::vector<Vertex> vertexes;
    int n;
    std::string file_name;
    bool answer_exist;
    int optimal_sum;
    int total_sum;
    std::chrono::microseconds running_time;
    std::vector<int> answer; // answer path
    std::vector<int> result_path;

    std::string result_file_name;
    std::string result_directory;

public:
    tsp(std::string file_name, bool answer_exist)
    {
        this->n = 0;
        this->file_name = file_name;
        this->answer_exist = answer_exist;
        this->total_sum = 0;
        this->optimal_sum = 0;
        read_tsp_file();
        if (answer_exist)
        {
            read_answer_file();
        }
    }
    void read_answer_file();
    void read_tsp_file();
    virtual void run_tsp();
    virtual void make_result_file();
};

class mst_2based
{
private:
    std::vector<Vertex> vertexes;
    int n;
    int cycle_cnt;
    bool answer_exist;
    int optimal_sum;
    std::string file_name;
    std::chrono::microseconds running_time;
    std::vector<int> answer;

public:
    mst_2based(std::string file_name, bool answer)
    {
        this->file_name = file_name;
        this->cycle_cnt = 0;
        this->answer_exist = answer;
        read_tsp_file();
        if (answer_exist)
        {
            read_answer_file();
        }
    }
    void read_answer_file();
    void read_tsp_file();
    std::vector<int> primMST();
    void preorderDFS(int u, const std::vector<std::vector<int>> &adj, std::vector<bool> &visited, std::vector<int> &tour);
    std::vector<int> tspApproximation();
    void func();
};

class myalgorithm : public tsp
{
private:
    std::vector<std::pair<int, int>> open_node_pairs; // {u, v} 형태로 저장
    int cycle_cnt;
    std::vector<int> cycle_couunt_vec;
    std::vector<int> cycle_connect_nodes;

public:
    myalgorithm(std::string file_name, bool answer) : tsp(file_name, answer)
    {
        /*nothing*/
        this->cycle_cnt = 0;
        this->result_file_name = this->file_name + "_myalgo";
        this->result_directory = "results/" + result_file_name;
        // std::cout << result_directory << std::endl;
    }
    void cycle_make();
    void cycle_cut();
    void cycle_connect();
    int count_cycle();
    bool has_open_chain();
    void func();
    void run_tsp();
    void make_result_file();
};

class christofied : public tsp
{
private:
    std::vector<int> euler_circuit;
    int mst_sum;

public:
    christofied(std::string file_name, bool answer_exist) : tsp(file_name, answer_exist)
    {
        this->mst_sum = 0;
        this->result_file_name = this->file_name + "_Christo";
        this->result_directory = "results/" + result_file_name;
    }
    void read_answer_file();
    void read_tsp_file();
    void MST();
    void perfect_matching();
    void hierholzer();
    void hamilton();
    void run_tsp()
    {
        auto start = std::chrono::high_resolution_clock::now();
        MST();
        perfect_matching();
        hierholzer();
        hamilton();
        auto end = std::chrono::high_resolution_clock::now();
        this->running_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    };
    void make_result_file()
    {
        std::cout << result_directory << std::endl;
        std::ofstream outFile(result_directory);
        // outFile.open(result_directory);
        outFile << "FILE NAME : " << this->file_name << '\n';
        outFile << "Total cost : " << this->total_sum << "\n";
        outFile << "MST cost : " << this->mst_sum << '\n';
        if (this->answer_exist)
        {
            outFile << "OPTIMAL COST : " << this->optimal_sum << "\n";
        }
        outFile << "ACTUAL RUNNING TIME : " << this->running_time.count() << "\n";
        outFile.close();
    }
};
#include <sys/resource.h>

static long get_rss_kb()
{
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return ru.ru_maxrss; // Linux: kB, macOS: bytes
}

class heldkarp : public tsp
{

private:
    int mst_sum;
public:
    heldkarp(std::string file_name, bool answer_exist) : tsp(file_name, answer_exist)
    {
        this->mst_sum = 0;
    }
    void run_tsp()
    {
        auto start = std::chrono::high_resolution_clock::now();
        run_tsp_helper();
        auto end = std::chrono::high_resolution_clock::now();
        this->running_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    };
    void run_tsp_helper();
    void make_result_file()
    {
        std::cout << result_directory << std::endl;
        std::ofstream outFile(result_directory);
        outFile << "FILE NAME : " << this->file_name << '\n';
        outFile << "Total cost : " << this->total_sum << "\n";
        if (this->answer_exist)
        {
            outFile << "OPTIMAL COST : " << this->optimal_sum << "\n";
        }
        outFile << "ACTUAL RUNNING TIME : " << this->running_time.count() << "\n";
        outFile.close();
    }
};

#endif