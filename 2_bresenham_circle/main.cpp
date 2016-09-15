#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <stdio.h>

int x1, y1, r;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

void draw(int x, int y) {
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
    int x, y, d;
    d = 1 - r;
    x = 0;
    y = r;
    draw(x, y);
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
        draw(x, y);
    }
}

void myDisplay() {
    drawCircle(r);
    glFlush();
}

int main(int argc, char **argv) {

    printf("Enter Circle Center (x1, y1) and radius (r)\n");
    scanf("%d %d %d", &x1, &y1, &r);

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
