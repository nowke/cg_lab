#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
using namespace std;

float x1 = 150, y1 = 150, x2 = 100, y2 = 300, x3 = 200, y3 = 400, x4 = 300, y4 = 300;
int left_edge[500], right_edge[500];

void draw_pixel(int x, int y) {
    glPointSize(1.0);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
}

void edgeDetect(float x1, float y1, float x2, float y2) {
    float mx, x;

    if(y1 > y2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    if(y1 == y2)
        mx = x2 - x1;
    else
        mx = (x2 - x1) / (y2 - y1);

    x = x1;

    for(int i = y1; i <= y2; i++) {
        if(x < left_edge[i])
            left_edge[i] = x;
        if(x > right_edge[i])
            right_edge[i] = x;

        x += mx;
    }
}

void scanfill(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
    for(int i = 0; i < 500; i++) {
        left_edge[i] = 500;
        right_edge[i] = 0;
    }

    edgeDetect(x1, y1, x2, y2);
    edgeDetect(x2, y2, x3, y3);
    edgeDetect(x3, y3, x4, y4);
    edgeDetect(x4, y4, x1, y1);

    for(int y = 0; y < 500; y++) {
        if(left_edge[y] <= right_edge[y]) {
            for(int i = left_edge[y]; i < right_edge[y]; i++) {
                draw_pixel(i, y);
            }
            glFlush();
        }
    }
}

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 500, 0, 500);
}

void scanfillDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    scanfill(x1, y1, x2, y2, x3, y3, x4, y4);
    glFlush();
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Original");
    myInit();
    glutDisplayFunc(myDisplay);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 0);
    glutCreateWindow("Scanfill");
    myInit();
    glutDisplayFunc(scanfillDisplay);
    glutMainLoop();
    return 0;
}