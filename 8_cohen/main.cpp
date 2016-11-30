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
double xmin = 100, ymin = 100, xmax = 200, ymax = 200;
double xwmin = 300, ywmin = 300, xwmax = 400, ywmax = 400;

const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int cnt = 0;

int computeCode(int x, int y) {
    int code = 0;
    if(x < xmin)
        code |= LEFT;
    else if(x > xmax)
        code |= RIGHT;

    if(y < ymin)
        code |= BOTTOM;
    else if(y > ymax)
        code |= TOP;

    return code;
}

void cohenSutherland(double x1, double y1, double x2, double y2) {
    int outcode0 = computeCode(x1, y1);
    int outcode1 = computeCode(x2, y2);

    bool accept = false;

    while(true) {
        if(!(outcode0 | outcode1)) { //Bitwise OR is 0, accept it since the points lie completely inside the clip window
            accept = true;
            break;
        }
        else if(outcode0 & outcode1) //Bitwise AND is not 0, reject it since the points lie completely outside the clip window
            break;
        else {
            //calculate line segment to clip from an outside point to an intersection with clip edge
            int outcodeOut = outcode0 ? outcode0 : outcode1;
            double x, y;
            double slope;
            slope = (y2 - y1) / (x2 - x1);

            if(outcodeOut & TOP) {
                x = x1 + (1 / slope) * (ymax - y1);
                y = ymax;
            }
            else if(outcodeOut & BOTTOM) {
                x = x1 + (1 / slope) * (ymin - y1);
                y = ymin;
            }
            else if(outcodeOut & RIGHT) {
                y = y1 + slope * (xmax - x1);
                x = xmax;
            }
            else {
                y = y1 + slope * (xmin - x1);
                x = xmin;
            }

            if(outcodeOut == outcode0) {
                x1 = x, y1 = y;
                outcode0 = computeCode(x1, y1);
            }
            else {
                x2 = x, y2 = y;
                outcode1 = computeCode(x2, y2);
            }
        }
    }

    if(accept) {
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

    cohenSutherland(x1, y1, x2, y2);
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
    glutCreateWindow("Cohen-Sutherland");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutMainLoop();
    return 0;
}