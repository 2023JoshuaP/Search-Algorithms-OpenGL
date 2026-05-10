#include <GL/glut.h>
#include "Point.h"
#include "Algorithms.h"
#include "delaunator.hpp"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

/* Global Variables */

const int NUM_POINTS = 1000;
const float MARGIN = 0.95f;
vector<vector<int>> graph;
vector<int> path;
vector<int> nodes_visited;
int current_algorithm_search = -1;

/* Setup OpenGL functionalities */

vector<Point> points;
vector<double> coords;
delaunator::Delaunator* triangulation = nullptr;
int start_point = -1;
int end_point = -1;

float screenToGLX(int x, int w) {
    return (float)x / w * 2.0f - 1.0f;
}

float screenToGLY(int y, int h) {
    return -((float)y / h * 2.0f - 1.0f);
}

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

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float glx = screenToGLX(x, 1100);
        float gly = screenToGLY(y, 800);
        int nearest = nearest_point(glx, gly);
        if (nearest != -1) {
            if (start_point == -1) {
                start_point = nearest;
                cout << "Start point: " << start_point << endl;
            }
            else if (end_point == -1) {
                end_point = nearest;
                cout << "End point: " << end_point << endl;
            }
            else {
                start_point = nearest;
                end_point = -1;
                cout << "Start point: " << start_point << endl;
            }
        }
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
    else if (key == '1') {
        run_algorithm(0);
    }
    else if (key == '2') {
        run_algorithm(1);
    }
    else if (key == '3') {
        run_algorithm(2);
    }
    else if (key == '4') {
        run_algorithm(3);
    }
    else if (key == '5') {
        run_algorithm(4);
    }
    else if (key == '6') {
        run_algorithm(5);
    }
    else if (key == '7') {
        run_algorithm(6);
    }
    else if (key == 'r' || key == 'R') {
        start_point = -1;
        end_point = -1;
        path.clear();
        nodes_visited.clear();
        glutPostRedisplay();
    }
    else if (key == 'g' || key == 'G') {
        generate_points();
        compute_triangulation();
        build_graph();
        start_point = -1;
        end_point = -1;
        path.clear();
        nodes_visited.clear();
        glutPostRedisplay();
    }
}

void draw_mesh() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);

    for (size_t i = 0; i < triangulation->triangles.size(); i += 3) {
        int t0 = triangulation->triangles[i];
        int t1 = triangulation->triangles[i + 1];
        int t2 = triangulation->triangles[i + 2];

        glVertex2f(points[t0].x, points[t0].y);
        glVertex2f(points[t1].x, points[t1].y);
        glVertex2f(points[t1].x, points[t1].y);
        glVertex2f(points[t2].x, points[t2].y);
        glVertex2f(points[t2].x, points[t2].y);
        glVertex2f(points[t0].x, points[t0].y); 
    }

    glEnd();
}

void draw_points() {
    glPointSize(7.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < (int)points.size(); i++) {
        if (i == start_point) {
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        else if (i == end_point) {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        else if (find(nodes_visited.begin(), nodes_visited.end(), i) != nodes_visited.end()) {
            glColor3f(1.0f, 1.0f, 0.0f);
        }
        else {
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        glVertex2f(points[i].x, points[i].y);
    }

    glEnd();
}

void draw_path() {
    if (path.size() < 2) {
        return;
    }

    glColor3f(0.0f, 0.5f, 1.0f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);

    for (int i = 0; i < (int)path.size() - 1; i++) {
        glVertex2f(points[path[i]].x, points[path[i]].y);
        glVertex2f(points[path[i + 1]].x, points[path[i + 1]].y);
    }

    glEnd();
    glLineWidth(1.0f);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_mesh();
    draw_path();
    draw_points();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    srand(time(0));
    generate_points();
    compute_triangulation();
    build_graph();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1100, 800);
    glutCreateWindow("Mesh");
    // glutFullScreen();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}