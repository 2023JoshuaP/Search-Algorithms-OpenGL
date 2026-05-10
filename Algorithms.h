#pragma once

#include "Point.h"
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;
using PQ = pair<float, int>;

vector<int> bfs(int start, int end, vector<vector<int>>& graph, vector<int>& visited);
vector<int> dfs(int start, int end, vector<vector<int>>& graph, vector<int>& visited);
vector<int> a_star(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited);
vector<int> greedy_best_first(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited);
vector<int> hill_climbing(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited);
vector<int> dijkstra(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited);
vector<int> ida_star(int start, int end, vector<vector<int>>& graph, vector<Point>& points, vector<int>& visited);