#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
using namespace std;

int x1, y1, x2, y2;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glColor3f(0.0, 0.0, 0.0);
}

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) {
    int incx = 1, incy = 1;

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;

    if (x2 < x1) incx = -1;
    if (y2 < y1) incy = -1;

    int x = x1;
    int y = y1;

    if (dx > dy) {
        // Slope less than 1
        draw_pixel(x, y);
        int e = 2 * dy - dx;
        for (int i = 0; i < dx; i++) {
            if (e >= 0) {
                y += incy;
                e += 2 * (dy - dx);
            }
            else
                e += 2 * dy;
            x += incx;
            draw_pixel(x, y);
        }

    } else {
        // Slope greater than 1
        draw_pixel(x, y);
        int e = 2 * dx - dy;
        for (int i = 0; i < dy; i++) {
            if (e >= 0) {
                x += incx;
                e += 2 * (dx - dy);;
            }
            else
                e += 2 * dx;
            y += incy;
            draw_pixel(x, y);
        }
    }
}

void myDisplay() {
    draw_line(x1, x2, y1, y2);
    glFlush();
}

int main(int argc, char **argv) {

    cout << "Enter (x1, y1), (x2, y2)" << endl;
    cin >> x1 >> y1 >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Line Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
