#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "delaunator.hpp"
using namespace std;

const int NUM_POINTS = 400;
const float MARGIN = 0.95f;

struct Point {
    float x;
    float y;
};

vector<Point> points;
vector<double> coords;
delaunator::Delaunator* triangulation = nullptr;

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

void draw_mesh() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINES);

    for (size_t i = 0; i < triangulation->triangles.size(); i += 3) {
        int t0 = triangulation->triangles[i];
        int t1 = triangulation->triangles[i + 1];
        int t2 = triangulation->triangles[i + 2];

        float x0 = points[t0].x, y0 = points[t0].y;
        float x1 = points[t1].x, y1 = points[t1].y;
        float x2 = points[t2].x, y2 = points[t2].y;

        glVertex2f(x0, y0), glVertex2f(x1, y1);
        glVertex2f(x1, y1), glVertex2f(x2, y2);
        glVertex2f(x2, y2), glVertex2f(x0, y0);
    }

    glEnd();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27)
        exit(0);
}

void draw_points() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(7.0f);
    glBegin(GL_POINTS);

    for (const auto& p : points) {
        glVertex2f(p.x, p.y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_mesh();
    draw_points();
    glFlush();
}

int main(int argc, char** argv) {
    srand(time(0));
    generate_points();
    compute_triangulation();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1100, 800);
    glutCreateWindow("Mesh");
    // glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}