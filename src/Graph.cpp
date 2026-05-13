#include "Graph.h"
#include "Globals.h"
#include "Algorithms.h"
#include <iostream>
#include <chrono>
#include <GL/glut.h>

int nearest_point(float x, float y) {
    int nearest = -1;
    float min_dist = 1e9f;
    for (int i = 0; i < (int)points.size(); i++) {
        float dx = points[i].x - x;
        float dy = points[i].y - y;
        float dist = dx * dx + dy * dy;
        if (dist < min_dist) {
            min_dist = dist;
            nearest = i;
        }
    }
    return nearest;
}

void build_graph() {
    graph.clear();
    graph.resize(points.size());

    for (size_t i = 0; i < triangulation->triangles.size(); i += 3) {
        int a = triangulation->triangles[i];
        int b = triangulation->triangles[i + 1];
        int c = triangulation->triangles[i + 2];

        graph[a].push_back(b); graph[b].push_back(a);
        graph[b].push_back(c); graph[c].push_back(b);
        graph[a].push_back(c); graph[c].push_back(a);
    }

    for (auto& neighbors : graph) {
        sort(neighbors.begin(), neighbors.end());
        neighbors.erase(unique(neighbors.begin(), neighbors.end()), neighbors.end());
    }
}

void generate_points() {
    points.clear();
    coords.clear();
    for (int i = 0; i < NUM_POINTS; i++) {
        Point p;
        p.x = (float)rand() / RAND_MAX * 2.0f * MARGIN - MARGIN;
        p.y = (float)rand() / RAND_MAX * 2.0f * MARGIN - MARGIN;
        points.push_back(p);
        coords.push_back(p.x);
        coords.push_back(p.y);
    }
}

void compute_triangulation() {
    delete triangulation;
    triangulation = new delaunator::Delaunator(coords);
}

void run_algorithm(int algorithm) {
    if (start_point == -1 || end_point == -1) {
        cout << "Please select both start and end points." << endl;
        return;
    }

    path.clear();
    nodes_visited.clear();

    string algorithm_name[] = {"BFS", "DFS", "A*", "Greedy Best-First", "Hill Climbing", "Dijkstra", "IDA*"};
    cout << "Running " << algorithm_name[algorithm] << "..." << endl;

    auto start_time = chrono::high_resolution_clock::now();

    if (algorithm == 0) {
        path = bfs(start_point, end_point, graph, nodes_visited);
    }
    else if (algorithm == 1) {
        path = dfs(start_point, end_point, graph, nodes_visited);
    }
    else if (algorithm == 2) {
        path = a_star(start_point, end_point, graph, points, nodes_visited);
    }
    else if (algorithm == 3) {
        path = greedy_best_first(start_point, end_point, graph, points, nodes_visited);
    }
    else if (algorithm == 4) {
        path = hill_climbing(start_point, end_point, graph, points, nodes_visited);
    }
    else if (algorithm == 5) {
        path = dijkstra(start_point, end_point, graph, points, nodes_visited);
    }
    else if (algorithm == 6) {
        path = ida_star(start_point, end_point, graph, points, nodes_visited);
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    if (path.empty()) {
        cout << "No path found." << endl;
    }
    else {
        cout << "Path length: " << path.size() << endl;
        cout << "Path: ";
        for (int i : path) cout << i << " ";
        cout << endl;
    }

    cout << "Visited: " << nodes_visited.size() << " nodes" << endl;
    cout << "Execution time: " << duration << " microseconds" << endl;
    glutPostRedisplay();
}