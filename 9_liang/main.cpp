#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
using namespace std;

double x1, y1, x2, y2;
double t1, t2;
double xmin = 100, ymin = 100, xmax = 200, ymax = 200;
double xwmin = 300, ywmin = 300, xwmax = 400, ywmax = 400;
int cnt = 0;

bool clipTest(double p, double q) {
    double t;
    if(p)
        t = q / p;
    if(p < 0.0) {
        if(t > t1)
            t1 = t;
        if(t > t2)
            return false;
    }
    else if(p > 0.0) {
        if(t < t2)
            t2 = t;
        if(t < t1)
            return false;
    }
    else if (p == 0.0) {
        if(q < 0.0)
            return false;

    }
    return true;
}

void liangBarsky(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1, dy = y2 - y1;
    t1 = 0.0, t2 = 1.0;

    if(clipTest(-dx, x1 - xmin))
    if(clipTest(dx, xmax - x1))
    if(clipTest(-dy, y1 - ymin))
    if(clipTest(dy, ymax - y1)) {
        if(t2 < 1.0) {
            x2 = x1 + t2 * dx;
            y2 = y1 + t2 * dy;
        }
        if(t1 > 0.0) {
            x1 = x1 + t1 * dx;
            y1 = y1 + t1 * dy;
        }

        //scale parameters
        double sx = (xwmax - xwmin) / (xmax - xmin);
        double sy = (ywmax - ywmin) / (ymax - ymin);
        double vx1 = xwmin + (x1 - xmin) * sx;
        double vy1 = ywmin + (y1 - ymin) * sy;
        double vx2 = xwmin + (x2 - xmin) * sx;
        double vy2 = ywmin + (y2 - ymin) * sy;

        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
        glVertex2f(vx1, vy1);
        glVertex2f(vx2, vy2);
        glEnd();
    }
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500.0, 0, 500.0);
}

void myDisplay() {
    //display line
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

    //display clipping window
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    //display clipped window
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xwmin, ywmin);
    glVertex2f(xwmax, ywmin);
    glVertex2f(xwmax, ywmax);
    glVertex2f(xwmin, ywmax);
    glEnd();

    liangBarsky(x1, y1, x2, y2);
    glFlush();
}

void myMouse(int button, int state, int x, int y) {
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cnt++;
        if (cnt == 1)
            x1 = x, y1 = y;
        else if (cnt == 2) {
            cnt = 0;
            x2 = x, y2 = y;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang Barsky");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}

