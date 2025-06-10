#include "tsp.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "utils.h"

void mst_2based::read_tsp_file() {
    std::string filename = "tsp/"+this->file_name + ".tsp";
    std::ifstream infile(filename);
    std::string line;

    // 0. DIMENSION 읽기
    while (std::getline(infile, line)) {
        // 앞뒤 공백 제거
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // DIMENSION 줄인지 확인
        if (line.find("DIMENSION") != std::string::npos) {
            // "DIMENSION : 280" 또는 "DIMENSION:280" 같은 포맷 처리
            size_t colon_pos = line.find(':');
            if (colon_pos != std::string::npos) {
                std::string num_str = line.substr(colon_pos + 1);
                num_str.erase(0, num_str.find_first_not_of(" \t\r\n"));
                this->n = std::stoi(num_str);
            }
        }

        // NODE_COORD_SECTION 도달 시 중단
        if (line == "NODE_COORD_SECTION") break;
    }

    // 1. 정점 정보 읽기
    while (std::getline(infile, line)) {
        if (line == "-1") break;

        std::istringstream iss(line);
        int index;
        double x, y;
        if (!(iss >> index >> x >> y)) continue;

        if (vertexes.size() < static_cast<size_t>(index))
            vertexes.resize(index);

        vertexes[index - 1].x = x;
        vertexes[index - 1].y = y;
    }
}


void mst_2based::read_answer_file() {
    std::string filename = "tsp/"+this->file_name + ".opt.tour";
    std::ifstream infile(filename);
    std::string line;

    // 1. "NODE_COORD_SECTION"까지 읽어넘김
    while (std::getline(infile, line)) {
        if (line == "TOUR_SECTION") break;
    }

    // 2. 정점 정보 읽기
    while (std::getline(infile, line)) {
        if (line == "-1") break;

        std::istringstream iss(line);
        int index;
        if (!(iss >> index)) continue; // 제대로 안 읽히면 skip

        // 정점 번호는 1-based지만 vector는 0-based 이므로 index-1
        if (vertexes.size() < static_cast<size_t>(index))
            vertexes.resize(index);
        answer.push_back(index-1);
    }
    for(int i=0; i<n-1; i++){
        this->optimal_sum += distance(vertexes[answer[i]] , vertexes[answer[i+1]]);
    }
    this->optimal_sum += distance(vertexes[answer[n-1]], vertexes[0]);

}
