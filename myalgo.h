#include "tsp.h"

class myalgorithm : public tsp{
private:
    int cycle_cnt;
    std::vector<std::pair<int, int>> open_node_pairs;  // {u, v} 형태로 저장
public:
    myalgorithm(std::string file_name,bool answer_exist) : 
        tsp(file_name,answer_exist)
    {
        this->cycle_cnt = 0;
    }
    void cycle_make();
    void cycle_cut();
    void cycle_connect();
    int count_cycle();
    bool has_open_chain();
    void run_myalgo();
};
