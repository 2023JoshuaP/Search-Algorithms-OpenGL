#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

const int NUM_POINTS = 400;
const float MARGIN = 0.95f;

struct Point {
    float x;
    float y;
};

vector<Point> points;

void generate_points() {
    for (int i = 0; i < NUM_POINTS; i++) {
        Point p;
        p.x = (float)rand() / RAND_MAX * 2.0f * MARGIN - MARGIN;
        p.y = (float)rand() / RAND_MAX * 2.0f * MARGIN - MARGIN;
        points.push_back(p);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);

    for (const auto& p : points) {
        glVertex2f(p.x, p.y);
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    srand(time(0));
    generate_points();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1100, 800);
    glutCreateWindow("Puntos");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}