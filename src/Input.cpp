#include "Input.h"
#include "Globals.h"
#include "delaunator.hpp"
#include "Graph.h"
#include "Renderer.h"
#include "Utils.h"
#include <GL/glut.h>
#include <iostream>

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float glx = screenToGLX(x, 1100);
        float gly = screenToGLY(y, 800);
        int nearest = nearest_point(glx, gly);
        if (nearest != -1) {
            if (start_point == -1) {
                start_point = nearest;
                std::cout << "Start point: " << start_point << std::endl;
            }
            else if (end_point == -1) {
                end_point = nearest;
                std::cout << "End point: " << end_point << std::endl;
            }
            else {
                start_point = nearest;
                end_point = -1;
                std::cout << "Start point: " << start_point << std::endl;
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