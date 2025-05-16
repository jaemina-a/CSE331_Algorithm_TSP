#include "christo.h"
#include "util.h"
#include <cmath>
int distance(const struct Vertex p1, const struct Vertex p2){
    double d1 = p1.x - p2.x;
    double d2 = p1.y - p2.y;
    double d = std::sqrt(static_cast<double>(d1*d1 + d2*d2));
    return static_cast<int>(d+0.5);
}

