#include <GL/glut.h>
#include "Renderer.h"
#include "Globals.h"
#include <algorithm>

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