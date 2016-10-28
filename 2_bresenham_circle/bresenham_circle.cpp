#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
using namespace std;

int x1, y1, r;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glColor3f(0.0, 0.0, 0.0);
}

void drawOctetPoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x + x1, y + y1);
    glVertex2i(-x + x1, y + y1);
    glVertex2i(x + x1, -y + y1);
    glVertex2i(-x + x1, -y + y1);
    glVertex2i(y + x1, x + y1);
    glVertex2i(-y + x1, x + y1);
    glVertex2i(y + x1, -x + y1);
    glVertex2i(-y + x1, -x + y1);
    glEnd();
}

void drawCircle(int r) {
    int d = 1 - r;
    int x = 0;
    int y = r;

    drawOctetPoints(x, y);
    while (x <= y) {
        if (d < 0) {
            x++;
            d = d + 2 * x + 1;
        }
        else {
            x++;
            y--;
            d = d + 2 * x - 2 * y + 1;
        }
        drawOctetPoints(x, y);
    }
}

void myDisplay() {
    drawCircle(r);
    glFlush();
}

int main(int argc, char **argv) {

    cout << "Enter Circle Center (x1, y1) and radius (r)" << endl;
    cin >> x1 >> y1 >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham's Circle Drawing");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
