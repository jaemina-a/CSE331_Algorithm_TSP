#ifndef UTILS_H
#define UTILS_H
#include "christo.h"
int distance(const struct Vertex p1, const struct Vertex p2);
void heapify(std::vector<Edge>& edges, int n, int i);
void heapSort(std::vector<Edge>& edges);

#endif