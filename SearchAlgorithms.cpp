#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "delaunator.hpp"

using namespace std;

const int NUM_POINTS = 1000;

vector<float> points;
vector<double> coords;
delaunator::Delaunator* d;

void generate_points() {
    points.clear();
    coords.clear();

    for (int i = 0; i < NUM_POINTS; i++) {
        float x = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float y = (float)rand() / RAND_MAX * 2.0f - 1.0f;

        points.push_back(x);
        points.push_back(y);

        coords.push_back(x);
        coords.push_back(y);
    }
}

void compute_delaunay() {
    d = new delaunator::Delaunator(coords);
}

void display() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (size_t i = 0; i < d->triangles.size(); i += 3) {

        int i0 = d->triangles[i];
        int i1 = d->triangles[i + 1];
        int i2 = d->triangles[i + 2];

        float x0 = points[2*i0], y0 = points[2*i0+1];
        float x1 = points[2*i1], y1 = points[2*i1+1];
        float x2 = points[2*i2], y2 = points[2*i2+1];

        glVertex2f(x0,y0); glVertex2f(x1,y1);
        glVertex2f(x1,y1); glVertex2f(x2,y2);
        glVertex2f(x2,y2); glVertex2f(x0,y0);
    }

    glEnd();

    // 🔹 Dibujar puntos encima
    glPointSize(3.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < points.size(); i += 2) {
        glVertex2f(points[i], points[i + 1]);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {

    srand(time(0));

    generate_points();
    compute_delaunay();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Delaunay Triangulation");

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}