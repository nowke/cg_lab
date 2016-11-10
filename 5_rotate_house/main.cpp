#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

GLfloat house[3][9]={ {100.0,100.0,250.0,250.0,175.0,150.0,150.0,200.0,200.0},
                      {100.0,300.0,300.0,100.0,400.0,100.0,150.0,150.0,100.0},
                      {1.0,   1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0  }  };

void myInit() {
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 500.0, -300, 500.0);
    glColor3f(0.0, 0.0, 0.0);
}


void draw_house() {
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(house[0][0],house[1][0]);
    glVertex2f(house[0][1],house[1][1]);
    glVertex2f(house[0][2],house[1][2]);
    glVertex2f(house[0][3],house[1][3]);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(house[0][5],house[1][5]);
    glVertex2f(house[0][6],house[1][6]);
    glVertex2f(house[0][7],house[1][7]);
    glVertex2f(house[0][8],house[1][8]);
    glEnd();
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(house[0][1],house[1][1]);
    glVertex2f(house[0][4],house[1][4]);
    glVertex2f(house[0][2],house[1][2]);
    glEnd();
}


void rotate() {
    glPushMatrix();
    glTranslatef(100,100,0.0);
    glRotatef(60, 0.0,0.0,1.0);
    glTranslatef(-100,-100,0.0);

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