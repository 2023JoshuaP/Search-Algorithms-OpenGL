#pragma once

#include <vector>
#include "Point.h"
#include "delaunator.hpp"

namespace delaunator {
    class Delaunator;
}

extern int NUM_POINTS;
extern float MARGIN;

extern std::vector<Point> points;
extern std::vector<double> coords;

extern std::vector<std::vector<int>> graph;
extern std::vector<int> path;
extern std::vector<int> nodes_visited;

extern delaunator::Delaunator* triangulation;

extern int start_point;
extern int end_point;