#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>

using namespace std;

GLfloat house[3][9]={ {100.0,100.0,250.0,250.0,175.0,150.0,150.0,200.0,200.0},
                      {100.0,300.0,300.0,100.0,400.0,100.0,150.0,150.0,100.0},
                      {1.0,   1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0  }  };

GLfloat theta,m,c;

void myInit() {
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
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

void reflect() {
    float sin1=sin(theta);
    float cos1=cos(theta);
    float x1=0;
    float x2=500;
    float y1=m*x1+c;
    float y2=m*x2+c;

    GLfloat m[16];
    for(int i=0;i<15;i++)
        m[i]=0.0;
    m[0]=cos1*cos1-sin1*sin1;
    m[1]=2*sin1*cos1;
    m[4]=2*sin1*cos1;
    m[5]=sin1*sin1-cos1*cos1;
    m[12]=2*(-c)*cos1*sin1;
    m[13] = 2 * c * cos1 * cos1;
    m[10]=1;
    m[15]=1;

    glPushMatrix();
    glMultMatrixf(m);
    draw_house();
    glPopMatrix();

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void display() {
    draw_house();
    reflect();
    glFlush();
}

int main(int argc, char* argv[]) {

    cout << "enter the value of m(y=mx+c):";

    cin >> m;
    cout << "Enter the value of c:";
    cin >> c;
    //theta=theta*3.141/180;
    theta=atan(m);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("house reflect");
    glutDisplayFunc(display);
    myInit();
    glutMainLoop();
    return 0;
}