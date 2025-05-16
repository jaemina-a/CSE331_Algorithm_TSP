#include <vector>
#include <string>
#include <iostream>
struct Vertex {
    double x,y;
    std::vector<int> connected; //vertex index를 저장하는 벡터
};

class christofied{
private:
    std::string file_name;
    int n;
    int mst_sum;
    int tsp_sum;
    int optimal_sum;
    bool answer_exist;
    std::vector<Vertex> vertexes; //all
    std::vector<int> answer;
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
        MST();
        perfect_matching();
        hierholzer();
        hamilton();
    };
    void print_result(){
        std::cout << "total cost : "<<this->tsp_sum << "\nmst cost : " << this->mst_sum << "\n";
        if(this->answer_exist){
            std::cout <<"optimal cost : " << this->optimal_sum << "\n";
        }
    }
};