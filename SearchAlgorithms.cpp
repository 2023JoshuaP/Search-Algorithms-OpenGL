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
    if (key == 27)
        exit(0);
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
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(7.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < (int)points.size(); i++) {
        if (i == start_point)
            glColor3f(0.0f, 1.0f, 0.0f); 
        else if (i == end_point)
            glColor3f(1.0f, 0.0f, 0.0f); 
        else
            glColor3f(1.0f, 1.0f, 1.0f); 

        glVertex2f(points[i].x, points[i].y);
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
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}