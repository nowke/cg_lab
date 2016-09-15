#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <math.h>

GLfloat v[4][3] = {
        {0.0, 0.0, 1.0},
        {0.0, 0.942809, -0.33333},
        {-0.816497, -0.471405, -0.333333},
        {0.816497, -0.471405, -0.333333}
};
int n;

void myInit() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void triangle(float* a, float* b, float* c) {
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void tetra(float* a, float* b, float* c, float* d) {
    glColor3f(1.0, 0.0, 0.0);
    triangle(a, b, c);
    glColor3f(0.0, 1.0, 0.0);
    triangle(a, c, d);
    glColor3f(0.0, 0.0, 1.0);
    triangle(a, d, b);
    glColor3f(0.0, 0.0, 0.0);
    triangle(b, d, c);
}

void divideTetra(float* a, float* b, float* c, float* d, int m) {
    float mid[6][3];
    if (m > 0) {
        for (int j=0; j<3; j++) {
            mid[0][j] = (a[j] + b[j]) / 2;
            mid[1][j] = (a[j] + c[j]) / 2;
            mid[2][j] = (a[j] + d[j]) / 2;
            mid[3][j] = (b[j] + c[j]) / 2;
            mid[4][j] = (c[j] + d[j]) / 2;
            mid[5][j] = (b[j] + d[j]) / 2;
        }
        divideTetra(a, mid[0], mid[1], mid[2], m-1);
        divideTetra(b, mid[0], mid[3], mid[5], m-1);
        divideTetra(c, mid[1], mid[3], mid[4], m-1);
        divideTetra(d, mid[2], mid[4], mid[5], m-1);
    } else {
        tetra(a, b, c, d);
    }
}

void myDisplay() {
    divideTetra(v[0], v[1], v[2], v[3], n);
    glFlush();
}

int main(int argc, char **argv) {

    n = 2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D Gasket");
    myInit();
    glutDisplayFunc(myDisplay);
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMainLoop();

    return 0;
}