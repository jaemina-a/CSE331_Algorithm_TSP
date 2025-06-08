#ifndef TSP_H
#define TSP_H
#include <vector>
#include <string>
#include <chrono>

struct Vertex {
    double x,y;
    std::vector<int> connected; //vertex index를 저장하는 벡터
    std::pair<int,int> closeV[2];
};

struct Edge {
    int u, v;
    int weight;
};
class tsp {
protected: // <-- 자식이 접근하려면 protected로!
    std::vector<Vertex> vertexes;
    int n;
    bool answer_exist;
    int optimal_sum;
    int tsp_sum;
    std::string file_name;
    std::chrono::microseconds running_time;
    std::vector<int> answer;
public:
    tsp(std::string file_name,bool answer_exist){
        this->file_name = file_name;
        this->answer_exist = answer_exist;
        read_tsp_file();
        if(answer_exist){
            read_answer_file();
        }
    }
    void read_answer_file();
    void read_tsp_file();
};

#endif