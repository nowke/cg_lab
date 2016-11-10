#include<iostream>

#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
using namespace std;
static GLfloat spin = 0.0;
int t, wid1, wid2;

void myinit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
}

void spinDisplay() {
    spin += 0.02;
    glutPostRedisplay();
}

void display1() {
    glutSetWindow(t);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glVertex3f(-0.25, 0.25, 0.25);
    glEnd();
    glPopMatrix();
    if (t == wid1) {
        glFlush();
        t = wid2;
    }
    else {
        glutSwapBuffers();
        t = wid1;
    }
}

void display2() {
    glutSetWindow(wid2);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
    glRotatef(spin, 0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.25, -0.25, 0.25);
    glVertex3f(0.25, -0.25, 0.25);
    glVertex3f(0.25, 0.25, 0.25);
    glVertex3f(-0.25, 0.25, 0.25);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void mouse1(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

void mouse2(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(spinDisplay);
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                glutIdleFunc(NULL);
            break;
        default:
            break;
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    wid1 = glutCreateWindow("Single");
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutDisplayFunc(display1);
    glutMouseFunc(mouse1);
    glutInitWindowSize(500, 500);
    wid1 = glutCreateWindow("Double");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    t = wid1;
    glutDisplayFunc(display1);
    glutMouseFunc(mouse2);
    myinit();
    glutMainLoop();
    return 0;
}