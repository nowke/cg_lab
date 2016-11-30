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

struct point {
    int x, y;
};

int curveNum;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.0, 600.0, 0.0, 500.0);
}

void lineSegment(point p1, point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void draw_curve(int curveNum) {
    int a = 175, b = 60;
    int x0 = 200, y0 = 250;
    float twoPi = 6.283185;
    float r, theta, dtheta = 1.0 / float(a);
    point curvePt[2];
    glColor3f(0.0, 0.0, 0.0);
    curvePt[0].x = x0;
    curvePt[0].y = y0;
    switch (curveNum) {
        case 1:
            curvePt[0].x += a + b;
            break;
        case 2:
            curvePt[0].x += a + a;
            break;
        case 3:
            curvePt[0].x += a;
            break;
        case 4:
            break;
        default:
            break;
    }
    theta = dtheta;
    while (theta < twoPi) {
        switch (curveNum) {
            case 1:
                r = a * cos(theta) + b;
                break;
            case 2:
                r = a * cos(theta) + a;
                break;
            case 3:
                r = a * cos(3 * theta);
                break;
            case 4:
                r = (a / 4.0) * theta;
                break;
            default:
                break;
        }
        curvePt[1].x = x0 + r * cos(theta);
        curvePt[1].y = y0 + r * sin(theta);
        lineSegment(curvePt[0], curvePt[1]);

        curvePt[0] = curvePt[1];
        theta += dtheta;
    }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    draw_curve(curveNum);
    glFlush();
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            curveNum = 1;
            break;
        case '2':
            curveNum = 2;
            break;
        case '3':
            curveNum = 3;
            break;
        case '4':
            curveNum = 4;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Limacon, Cardiod, Three-Leaf and Spiral");
    myInit();
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
}