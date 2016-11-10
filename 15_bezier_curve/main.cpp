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

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0.0, 800, 0.0, 800);
}

void myDisplay() {
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

int main(int argc, char **argv) {
    cout << "Enter x coordinates :" << endl;
    for(int i = 0; i < 4; i++)
        cin >> x[i];
    cout << "Enter y coordinates :" << endl;
    for(int i = 0; i < 4; i++)
        cin >> y[i];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bezier Curve");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
}