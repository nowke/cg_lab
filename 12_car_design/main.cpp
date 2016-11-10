#include<iostream>

#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
using namespace std;

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 't':
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
        default:
            break;
    }
}

void draw_wheel()
{
    glColor3f(0.0, 1.0, 0.0);
    glutSolidSphere(0.1, 16, 16);
}

void draw_car_body()
{
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.0, 0.25, 0.0);
    glVertex3f(0.9, 0.25, 0.0);
    glVertex3f(0.9, 0.55, 0.0);
    glVertex3f(0.8,0.55,0.0);
    glVertex3f(0.8,0.75,0.0);
    glVertex3f(0.2,0.75,0.0);
    glVertex3f(0.2,0.55,0.0);
    glVertex3f(0.0, 0.55, 0.0);
    glEnd();
}

void draw_body_and_wheel()

{
    glTranslatef(0.05, 0.0, 0.0);
    draw_car_body();
    glPushMatrix();
    glTranslatef(0.25, 0.25, 0.0);      //move to first wheel position
    draw_wheel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.75, 0.25, 0.0);     //move to 2nd wheel position
    draw_wheel();
    glPopMatrix();
    // draw last two wheels similar
}


void display(void)

{

    /* clear all pixels */

    glClear(GL_COLOR_BUFFER_BIT);

    // draw
    draw_body_and_wheel();


    /* don't wait! start processing buffered OpenGL routines */

    glFlush();

}

void init(void)

{

    /* select clearing (background) color */

    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* initialize viewing values */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(0.5, 0.5, 0.0);

}

/* main program to open a window and display a polygon */

int main(int argc, char** argv)

{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("a car: t to translate");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}