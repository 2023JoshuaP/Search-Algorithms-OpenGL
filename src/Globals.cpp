#include "Globals.h"

int NUM_POINTS = 1000;
float MARGIN = 1.0f;

std::vector<Point> points;
std::vector<double> coords;

std::vector<std::vector<int>> graph;
std::vector<int> path;
std::vector<int> nodes_visited;

delaunator::Delaunator* triangulation = nullptr;

int start_point = -1;
int end_point = -1;