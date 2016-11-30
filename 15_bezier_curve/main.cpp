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

float x[4], y[4];

int cnt = 0;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0.0, 500, 0.0, 500);
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    double xt, yt;
    glPointSize(4.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for(double t = 0.0; t <= 1.0; t += 0.0005) {
        xt = pow(1 - t, 3) * x[0] + 3 * pow(1 - t, 2) * t * x[1] + 3 * (1 - t) * pow(t, 2) * x[2] + pow(t, 3) * x[3];
        yt = pow(1 - t, 3) * y[0] + 3 * pow(1 - t, 2) * t * y[1] + 3 * (1 - t) * pow(t, 2) * y[2] + pow(t, 3) * y[3];
        glVertex2f(xt, yt);
    }
    glColor3f(1.0, 0.0, 0.0);
    for(int i = 0; i < 4; i++)
        glVertex2f(x[i], y[i]);
    glEnd();
    glFlush();
}

void myMouse(int button, int state, int cx, int cy) {
    cy = 500 - cy;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        cnt++;
        if (cnt == 1)
            x[0] = cx, y[0] = cy;
        else if (cnt == 2)
            x[1] = cx, y[1] = cy;
        else if (cnt == 3)
            x[2] = cx, y[2] = cy;
        else if (cnt == 4) {
            x[3] = cx, y[3] = cy;
            cnt = 0;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char **argv) {
//    cout << "Enter x coordinates :" << endl;
//    for(int i = 0; i < 4; i++)
//        cin >> x[i];
//    cout << "Enter y coordinates :" << endl;
//    for(int i = 0; i < 4; i++)
//        cin >> y[i];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bezier Curve");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
}