#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

int x1 = 400, y1 = 400, r = 50;

int para[4][2] = {
        {50, 50},
        {200, 50},
        {250, 200},
        {100, 200}
};

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 700, 0, 700);
}
/* Cylinder */


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
    glColor3f(1.0, 0.0, 0.0);
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

/* Parallelopiped */
void drawPara(int inc) {
    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(para[0][0] + inc, para[0][1] + inc);
    glVertex2i(para[1][0] + inc, para[1][1] + inc);
    glVertex2i(para[2][0] + inc, para[2][1] + inc);
    glVertex2i(para[3][0] + inc, para[3][1] + inc);
    glEnd();
}

void myDisplay() {
    for (int i=0; i<100; i+=2) {
        drawPara(i);
    }
    for (int i=0; i<25; i++) {
        drawCircle(r);
        y1 += 3;
    }

    glFlush();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Parallelopiped");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}