#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
using namespace std;

float vertices[] = {-1.0, -1.0, -1.0,
                       1.0, -1.0, -1.0,
                       1.0, 1.0, -1.0,
                      -1.0, 1.0, -1.0,
                      -1.0, -1.0, 1.0,
                       1.0, -1.0, 1.0,
                       1.0, 1.0, 1.0,
                      -1.0, 1.0, 1.0};
float colors[] = {0.0, 0.0, 0.0,
                    1.0, 0.0, 0.0,
                    1.0, 1.0, 0.0,
                    0.0, 1.0, 0.0,
                    0.0, 0.0, 1.0,
                    0.0, 1.0, 1.0};
GLubyte cube_indices[] = {0, 1, 2, 3,
                          5, 1, 2, 6,
                          4, 5, 6, 7,
                          0, 4, 7, 3,
                          2, 3, 7, 6,
                          0, 1, 5, 4};
float theta[] = {0.0, 0.0, 0.0};
int axis = 2;

void myInit() {
    glMatrixMode(GL_PROJECTION);
    glOrtho(-2.0, 2.0 , -2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
    glFlush();
}

void cube_spin() {
    theta[axis] += 2.0;
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cube Spin");
    myInit();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(cube_spin);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glutMainLoop();
}