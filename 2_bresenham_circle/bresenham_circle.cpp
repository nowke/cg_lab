#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glut.h>

#endif

#include <iostream>
#include <math.h>
using namespace std;

int cx1, cy1, r;
int cnt = 0;

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 500, 0, 500);
	glColor3f(0.0, 0.0, 0.0);
}

void drawOctetPoints(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x + cx1, y + cy1);
	glVertex2i(-x + cx1, y + cy1);
	glVertex2i(x + cx1, -y + cy1);
	glVertex2i(-x + cx1, -y + cy1);
	glVertex2i(y + cx1, x + cy1);
	glVertex2i(-y + cx1, x + cy1);
	glVertex2i(y + cx1, -x + cy1);
	glVertex2i(-y + cx1, -x + cy1);
	glEnd();
}

void drawCircle(int r) {
	int d = 1 - r;
	int x = 0;
	int y = r;

	drawOctetPoints(x, y);
	while (x <= y) {
		if (d >= 0) {
			x++;
			y--;
			d = d + 2 * x - 2 * y + 1; // d += 2x - 2y + 1
		} else {
			x++;
			d = d + 2 * x + 1; // d += 2x + 1
		}
		drawOctetPoints(x, y);
	}
}

void myDisplay() {
	drawCircle(r);
	glFlush();
}

void myMouse(int button, int state, int x, int y) {
    y = 500 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        cnt++;
        if (cnt == 1) {
            cx1 = x, cy1 = y;
        } else if (cnt == 2) {
            r = (int) sqrt((cx1 - x)*(cx1 - x) + (cy1 - y)*(cy1 - y));
            cnt = 0;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char **argv) {

//	cout << "Enter Circle Center (x1, y1) and radius (r)" << endl;
//	cin >> cx1 >> cy1 >> r;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Circle Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouse);
	glutMainLoop();

	return 0;
}
