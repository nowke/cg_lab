#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>

using namespace std;


double xmin = 50, ymin = 50, xmax = 100, ymax = 100; // Window boundaries
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300; // Viewport boundaries


int cliptest(double p, double q, double *t1, double *t2) {
    double r;
    if (p) r = q / p;  // to check whether p
    if (p < 0.0)    // potentially entry point, update te
    {
        if (r > *t1) *t1 = r;
        if (r > *t2) return (false); // line portion is outside
    }
    else if (p > 0.0)    //  Potentially leaving point, update tl
    {
        if (r < *t2) *t2 = r;
        if (r < *t1) return (false); // line portion is outside
    }
    else if (p == 0.0) {
        if (q < 0.0) return (false); // line parallel to edge but outside
    }
    return (true);
}

void LiangBarskyLineClipAndDraw(double x0, double y0, double x1, double y1) {
    double dx = x1 - x0, dy = y1 - y0, t1 = 0.0, t2 = 1.0;

    //draw a red colored viewport
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin, yvmin);
    glVertex2f(xvmax, yvmin);
    glVertex2f(xvmax, yvmax);
    glVertex2f(xvmin, yvmax);
    glEnd();

    if (cliptest(-dx, x0 - xmin, &t1, &t2))  // inside test wrt left edge
    if (cliptest(dx, xmax - x0, &t1, &t2)) // inside test wrt right edge
    if (cliptest(-dy, y0 - ymin, &t1, &t2)) // inside test wrt bottom edge
    if (cliptest(dy, ymax - y0, &t1, &t2)) // inside test wrt top edge
    {

        if (t2 < 1.0) {
            x1 = x0 + t2 * dx;
            y1 = y0 + t2 * dy;
        }

        if (t1 > 0.0) {
            x0 = x0 + t1 * dx;
            y0 = y0 + t1 * dy;
        }
        // Window to viewport mappings
        double sx = (xvmax - xvmin) / (xmax - xmin); // Scale parameters
        double sy = (yvmax - yvmin) / (ymax - ymin);
        double vx0 = xvmin + (x0 - xmin) * sx;
        double vy0 = yvmin + (y0 - ymin) * sy;
        double vx1 = xvmin + (x1 - xmin) * sx;
        double vy1 = yvmin + (y1 - ymin) * sy;

        glColor3f(0.0, 0.0, 1.0); // draw blue colored clipped line
        glBegin(GL_LINES);
        glVertex2d(vx0, vy0);
        glVertex2d(vx1, vy1);
        glEnd();
    }
}

// end of line clipping
void display() {
    double x0 = 60, y0 = 60, x1 = 90, y1 = 90;
    double p0 = 110, q0 = 30, p1 = 30, q1 = 120;
    glClear(GL_COLOR_BUFFER_BIT);
//draw the line with red color
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);

    glVertex2d(p0, q0);
    glVertex2d(p1, q1);

    glEnd();

//draw a blue colored window
    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    LiangBarskyLineClipAndDraw(x0, y0, x1, y1);
    LiangBarskyLineClipAndDraw(p0, q0, p1, q1);

    glFlush();
}

void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Liang Barsky Line Clipping Algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
