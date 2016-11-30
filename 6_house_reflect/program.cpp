#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <iostream>
 float m,c,theta;
 void myInit()
 {
     glClearColor(1,1,1,1);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-500,500,-500,500);
 }
 void drawhouse()
 {
     glBegin(GL_LINE_LOOP);
         glVertex2f(100,100);
         glVertex2f(100,200);
         glVertex2f(200,200);
         glVertex2f(200,100);
     glEnd();
     glBegin(GL_LINE_LOOP);
         glVertex2f(100,200);
         glVertex2f(150,250);
         glVertex2f(200,200);
     glEnd();
     glBegin(GL_LINE_LOOP);
         glVertex2f(130,100);
         glVertex2f(130,130);
         glVertex2f(170,130);
         glVertex2f(170,100);
     glEnd();
 }
 void myDisplay()
 {
     glClear(GL_COLOR_BUFFER_BIT);
     float x1,x2,y1,y2;
     x1=-500;
     x2=500;
     y1=m*x1+c;
     y2=m*x2+c;
     theta=(float)atan(m);
     theta = theta*180/3.14159265;
     glColor3f(0,1,0);
     glBegin(GL_LINES);
         glVertex2f(x1,y1);
         glVertex2f(x2,y2);
     glEnd();
     glColor3f(1,0,0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     drawhouse();
     glTranslatef(0,c,0);
     glRotatef(theta,0,0,1);
     glScalef(1,-1,1);
     glRotatef(-theta,0,0,1);
     glTranslatef(0,-c,0);
     drawhouse();
     glFlush();
 }
 int main(int argc,char **argv)
 {
     printf("\nenter the slope and inercept : ");
     scanf("%f%f",&m,&c);
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
     glutInitWindowSize(500,500);
     glutInitWindowPosition(0,0);
     glutCreateWindow("House Reflect");
     glutDisplayFunc(myDisplay);
     myInit();
     glutMainLoop();
     return 0;
 }
