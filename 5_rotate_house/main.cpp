#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

float house[][2] = {{100, 100}, {100, 300}, {250, 300},
                    {250, 100}, {175, 400}, {150, 100},
                    {150, 150}, {200, 150}, {200, 100}};

float pivot[] = {100, 100}; // Pivot Point
float angle = 90; // Angle of rotation in degree

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

void rotate() {
    glPushMatrix();

    glTranslatef(pivot[0], pivot[1], 0.0);
    glRotatef(angle, 0.0, 0.0, 1.0); // Rotate around z-axis
    glTranslatef(-pivot[0], -pivot[1], 0.0);

    draw_house();

    glPopMatrix();
}

void display() {
    draw_house();
    rotate();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("house rotation");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();

    return 0;
}