#include <GL/glut.h>
#include <cstdlib>

const int NUM_POINTS = 1000;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);

    for (int i = 0; i < NUM_POINTS; i++) {

        float x = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float y = (float)rand() / RAND_MAX * 2.0f - 1.0f;

        glVertex2f(x, y);
    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1100, 800);
    glutCreateWindow("Puntos");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}