#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <math.h>

float house[][2] = {{100, 100}, {100, 300}, {250, 300},
                    {250, 100}, {175, 400}, {150, 100},
                    {150, 150}, {200, 150}, {200, 100}};

float m = 5, c = 100, theta;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(-300, 500.0, -300, 500.0);
}

void draw_house() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2fv(house[0]);
        glVertex2fv(house[1]);
        glVertex2fv(house[2]);
        glVertex2fv(house[3]);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2fv(house[5]);
        glVertex2fv(house[6]);
        glVertex2fv(house[7]);
        glVertex2fv(house[8]);
    glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2fv(house[1]);
        glVertex2fv(house[4]);
        glVertex2fv(house[2]);
    glEnd();
}

void reflect() {
    // Draw the Axis for reflection
    float x1 = -500, x2 = 500;
    float y1 = m * x1 + c;
    float y2 = m * x2 + c;

    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();

    // Reflect
    glTranslatef(0, c, 0);
    glRotatef(theta, 0, 0, 1);
    glScalef(1, -1, 1);
    glRotatef(-theta, 0, 0, 1);
    glTranslatef(0,-c, 0);
    draw_house();
}

void display() {
    draw_house();
    reflect();
    glFlush();
}

int main(int argc, char* argv[]) {

    theta = atan(m);
    theta = theta * 180 / 3.14159265;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("House Reflection");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();

    return 0;
}