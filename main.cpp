#include <GL/glut.h>

#include "include/Graph.h"
#include "include/Renderer.h"
#include "include/Input.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {

    srand(time(0));

    generate_points();
    compute_triangulation();
    build_graph();

    cout << "List of algorithms:" << endl;
    cout << "1. BFS" << endl;
    cout << "2. DFS" << endl;
    cout << "3. A*" << endl;
    cout << "4. Greedy Best-First" << endl;
    cout << "5. Hill Climbing" << endl;
    cout << "6. Dijkstra" << endl;
    cout << "7. IDA*" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1100, 800);

    glutCreateWindow("Search Algorithms Visualization");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}