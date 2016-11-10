#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

#define outcode int
#define true 1
#define false 0

double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;

const int RIGHT=2;
const int LEFT=1;
const int TOP=8;
const int BOTTOM=4;

outcode computeoutcode(double x,double y)
{
    outcode code=0;
    if(y>ymax)
        code|=TOP;
    else if(y<ymin)
        code|=BOTTOM;

    if(x>xmax)
        code|=RIGHT;
    else if(x<xmin)
        code|=LEFT;

    return code;
}

void cohensuther(double x0,double y0,double x1,double y1)
{
    outcode outcode0,outcode1,outcodeout;
    bool accept=false,done=false;

    outcode0=computeoutcode(x0,y0);
    outcode1=computeoutcode(x1,y1);

    cout << "outcode0 " << outcode0 << endl;
    cout << "outcode1 " << outcode1 << endl;
    cout << endl;

    do
    {
        if(!(outcode0|outcode1)) {
            accept=true;
            done=true;
        }
        else if(outcode0 & outcode1)
            done=true;
        else {
            double x,y;
            outcodeout=outcode0 ? outcode0 : outcode1;
            if(outcodeout & TOP)
            {
                x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y=ymax;
            }
            else if(outcodeout & BOTTOM)
            {
                x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y=ymin;
            }
            else if(outcodeout & RIGHT)
            {
                y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            }
            else
            {
                y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }

            if(outcodeout ==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=computeoutcode(x0,y0);
            }
            else
            {
                x1=x;
                y1=y;
                outcode1=computeoutcode(x1,y1);
            }
        }

    }while(!done);

    if(accept)
    {
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);

        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;

        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2f(xvmin,yvmin);
        glVertex2f(xvmax,yvmin);
        glVertex2f(xvmax,yvmax);
        glVertex2f(xvmin,yvmax);
        glEnd();

        glColor3f(0,0,1);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
    }
}

void display()
{
    double x0=120,y0=10,x1=40,y1=130;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2d(x0,y0);
    glVertex2d(x1,y1);
    glVertex2d(60,20);
    glVertex2d(80,120);
    glVertex2d(60,60);
    glVertex2d(80,80);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();

    cohensuther(x0,y0,x1,y1);
    cohensuther(60,20,80,120);
    cohensuther(60,60,80,80);

    glFlush();
}
void myinit()
{
    glClearColor(1,1,1,1);
    glColor3f(1,0,0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("clip");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
}