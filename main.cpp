#include "christo.h"
#include <cmath>
#include <vector>
#include <iostream>




int main() {
    std::string file_name = "tsp/kz9976";
    christofied my_christo(file_name,true);
    my_christo.tsp();
    my_christo.print_result();
    return 0;
}