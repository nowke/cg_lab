#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
#include <math.h>
using namespace std;

int single_buffer, double_buffer;
float x, y, spin = 0.0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-2, 2, -2, 2);
}

void square() {
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x, y);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-y, x);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-x, -y);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(y, -x);
    glEnd();
}

void display_single() {
    glClear(GL_COLOR_BUFFER_BIT);
    square();
    glFlush();
}

void display_double() {
    glClear(GL_COLOR_BUFFER_BIT);
    square();
    glutSwapBuffers();
}

void spin_display() {
    spin += 0.025; // Radian
    x =  cos(spin);
    y = sin(spin);

    glutSetWindow(single_buffer);
    glutPostRedisplay();
    glutSetWindow(double_buffer);
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        glutIdleFunc(spin_display);
    if(btn == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        glutIdleFunc(NULL);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    single_buffer = glutCreateWindow("Single Buffer");
    myInit();
    glutDisplayFunc(display_single);
    glutIdleFunc(spin_display);
    glutMouseFunc(mouse);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 0);
    double_buffer = glutCreateWindow("Double Buffer");
    myInit();
    glutDisplayFunc(display_double);
    glutIdleFunc(spin_display);
    glutMouseFunc(mouse);

    glutMainLoop();
}