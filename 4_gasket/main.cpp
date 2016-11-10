#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

float v[4][3]={{0,200,400},{0,0,-350},{-300,300,200},{200,300,350}};
int n;

void myInit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-500, 500, -500, 500, -500, 500);
}

void triangle(float* a, float* b, float* c) {
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void divideTriangle(float* a, float* b, float* c, int m) {
    float mid[3][3];
    if (m > 0) {
        for (int j=0; j<3; j++) {
            mid[0][j] = (a[j] + b[j]) /2;
            mid[1][j] = (b[j] + c[j]) /2;
            mid[2][j] = (a[j] + c[j]) /2;
        }
        divideTriangle(a, mid[0], mid[2], m-1);
        divideTriangle(b, mid[0], mid[1], m-1);
        divideTriangle(c, mid[1], mid[2], m-1);
    } else {
        triangle(a, b, c);
    }

}

void myDisplay() {
    glColor3f(1.0, 0.0, 0.0);
    divideTriangle(v[0], v[1], v[2], n);
    glColor3f(0.0, 1.0, 0.0);
    divideTriangle(v[0], v[2], v[3], n);
    glColor3f(0.0, 0.0, 1.0);
    divideTriangle(v[0], v[1], v[3], n);
    glColor3f(1.0, 1.0, 1.0);
    divideTriangle(v[1], v[2], v[3], n);
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
    glutMainLoop();

    return 0;
}