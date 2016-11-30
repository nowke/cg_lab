#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <math.h>

struct vertex
{
	float x, y;
};


vertex w[4];        // 4 vertices for clipping window
vertex ip_ver[4];   // 4 input polygon vertices
vertex op_ver[10];  // a buffer for output vertices
int n_in, n_out;    // number of input & output vertices in the buffers


					// draw a polygon of n vertices
void draw_polygon(vertex * p, int n)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2f(p[i].x, p[i].y);
	glEnd();
}


// add vertex to output buffer
void add_op_vertex(vertex p)
{

	op_ver[n_out] = p;
	n_out = n_out + 1;
}


// check if a vertex is inside with respect to given edge
bool is_inside(vertex p, int edge)
{
	if ((edge == 0) && (p.x >= w[0].x))       // inside wrt left edge
		return true;
	else if ((edge == 1) && (p.x <= w[1].x))  // inside wrt right edge
		return true;
	else if ((edge == 2) && (p.y <= w[2].y))  // inside wrt top edge
		return true;
	else if ((edge == 3) && (p.y >= w[0].y))  // inside wrt bottom edge
		return true;
	return false;
}


// get the intersection point of
vertex get_intersection_ver(vertex v1, vertex v2, int edge)
{
	vertex in;  // intersection vertex
	float m = (v2.y - v1.y) / (v2.x - v1.x);        // slope of line = dy/dx

	if (edge == 0)
	{
		// left clipping edge
		in.x = w[0].x;
		in.y = m * (in.x - v1.x) + v1.y;
	}
	else if (edge == 1)
	{
		// right clipping edge
		in.x = w[1].x;
		in.y = m * (in.x - v1.x) + v1.y;
	}
	else if (edge == 2)
	{
		// top clipping edge
		in.y = w[3].y;
		in.x = 1.0 / m * (in.y - v1.y) + v1.x;
	}
	else if (edge == 3)
	{
		// bottom clipping edge
		in.y = w[0].y;
		in.x = 1.0 / m * (in.y - v1.y) + v1.x;
	}
	return in;
}


// clipper
void clip(vertex * ip_ver, int n_in)
{
	vertex v1, v2, interSec;
	for (int edge = 0; edge < 4; edge++)
	{
		n_out = 0;
		for (int j = 0; j < n_in; j++)
		{
			v1 = ip_ver[j];                // first vertex
			v2 = ip_ver[(j + 1) % n_in];   // second vertex

			if (is_inside(v1, edge))
			{
				if (is_inside(v2, edge))
				{
					// If both input vertices are inside this clipping-window border,
					// only the second vertex is sent to the next clipper.
					add_op_vertex(v2);
				}
				else
				{
					// If the first vertex is inside this clipping-window border and
					// the second vertex is outside,  only the polygon edge-intersection
					// position with the clipping-window border is sent to the next clipper
					interSec = get_intersection_ver(v1, v2, edge);
					add_op_vertex(interSec);
				}
			}
			else
			{
				if (is_inside(v2, edge))
				{
					// If the first input vertex is outside this clipping-window border and
					// the second vertex is inside,  both the intersection vertex of the
					// polygon edge with the window border and the second vertex are sent to
					// the next clipper.
					interSec = get_intersection_ver(v1, v2, edge);
					add_op_vertex(interSec);
					add_op_vertex(v2);
				}
			}
		}

		// copy output vertices to input vertices
		for (int k = 0; k < n_out; k++)
		{
			ip_ver[k].x = op_ver[k].x;
			ip_ver[k].y = op_ver[k].y;
		}
		n_in = n_out;
	}
}


void display(void)
{
	// draw the clipping window
	glColor3f(1.0f, 0.0f, 0.0f);
	draw_polygon(w, 4);

	glColor3f(0.0f, 1.0f, 0.0f);
	draw_polygon(ip_ver, 4);

	// clip the polygon
	clip(ip_ver, 4);

	// draw the polygon
	glColor3f(0.0f, 0.0f, 1.0f);
	draw_polygon(op_ver, n_out);

	glFlush();
}


void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// setup the clipping window
	w[0].x = 20; w[0].y = 10;
	w[1].x = 80; w[1].y = 10;
	w[2].x = 80; w[2].y = 80;
	w[3].x = 20; w[3].y = 80;

	// setup the input polygon
	ip_ver[0].x = 50; ip_ver[0].y = 5;
	ip_ver[1].x = 90; ip_ver[1].y = 40;
	ip_ver[2].x = 60; ip_ver[2].y = 90;
	ip_ver[3].x = 5; ip_ver[3].y = 30;
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Polygon Clipping :)");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
