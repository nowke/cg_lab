#ifdef __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <iostream>
#include <vector>

using namespace std;

typedef struct Point {
    int x, y;
} Point;

int clip_window[][2] = {{200, 200}, {400, 200}, {400, 400}, {200, 400}};
//int polygon_array[][2] ={{250, 50}, {250, 350}, {50, 300}};
int polygon_array[][2] ={{150, 300}, {300, 100}, {450, 350}, {300, 450}};

void myInit() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

vector<Point> polygon;

void setup_polygon() {
    for (int i=0; i< sizeof(polygon_array) / 8; i++) {
        Point p;
        p.x = polygon_array[i][0], p.y = polygon_array[i][1];
        polygon.push_back(p);
    }
}

void clip_left_edge() {
    vector<Point> new_polygon;
    int n = (int) polygon.size();
    for (int i=0; i<n; i++) {
        Point v1 = polygon[i];
        Point v2 = polygon[(i + 1) % n];

        int left_edge_x = clip_window[0][0];

        // Check x coordinates

        // CASE 1 -> Outside to Inside
        if (v1.x <= left_edge_x && v2.x > left_edge_x) {
            // Find intersection (x, y)
            double slope = (double)(v1.y - v2.y) / (v1.x - v2.x);
            int x = left_edge_x;
            int y =  (int) (v1.y + slope * (left_edge_x - v1.x));

            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
            new_polygon.push_back(v2);
        }

        // CASE 2 -> Both outside (Leave)

        // CASE 3 -> Both inside
        if (v1.x > left_edge_x && v2.x > left_edge_x) {
            new_polygon.push_back(v2);
        }

        // CASE 4 -> Inside To Outside
        if (v1.x > left_edge_x && v2.x <= left_edge_x) {
            // Find intersection (x, y)
            double slope = (double)(v1.y - v2.y) / (v1.x - v2.x);
            int x = left_edge_x;
            int y =  (int) (v2.y + slope * (left_edge_x - v2.x));
            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
        }
    }

    polygon = new_polygon;
}

void clip_right_edge() {
    vector<Point> new_polygon;
    int n = (int) polygon.size();
    for (int i=0; i<n; i++) {
        Point v1 = polygon[i];
        Point v2 = polygon[(i + 1) % n];

        int right_edge_x = clip_window[1][0];

        // Check x coordinates

        // CASE 1 -> Outside to Inside
        if (v1.x >= right_edge_x && v2.x < right_edge_x) {
            // Find intersection (x, y)
            double slope = (double)(v1.y - v2.y) / (v1.x - v2.x);
            int x = right_edge_x;
            int y =  (int) (v1.y + slope * (right_edge_x - v1.x));
            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
            new_polygon.push_back(v2);
        }

        // CASE 2 -> Both outside (Leave)

        // CASE 3 -> Both inside
        if (v1.x < right_edge_x && v2.x < right_edge_x) {
            new_polygon.push_back(v2);
        }

        // CASE 4 -> Inside To Outside
        if (v1.x < right_edge_x && v2.x >= right_edge_x) {
            // Find intersection (x, y)
            double slope = (double)(v1.y - v2.y) / (v1.x - v2.x);
            int x = right_edge_x;
            int y =  (int) (v2.y + slope * (right_edge_x - v2.x));

            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
        }
    }

    polygon = new_polygon;
}

void clip_bottom_edge() {
    vector<Point> new_polygon;
    int n = (int) polygon.size();
    for (int i=0; i<n; i++) {
        Point v1 = polygon[i];
        Point v2 = polygon[(i + 1) % n];

        int bottom_edge_y = clip_window[0][1];

        // Check y coordinates

        // CASE 1 -> Outside to Inside
        if (v1.y <= bottom_edge_y && v2.y > bottom_edge_y) {
            int x, y;
            // Find intersection (x, y)
            if (v1.x == v2.x) {
                y = bottom_edge_y;
                x = v1.x;
            } else {
                double slope = (double) (v1.y - v2.y) / (v1.x - v2.x);
                y = bottom_edge_y;
                x = (int) (v1.x + (1 / slope) * (bottom_edge_y - v1.y));
            }
            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
            new_polygon.push_back(v2);
        }

        // CASE 2 -> Both outside (Leave)

        // CASE 3 -> Both inside
        if (v1.y > bottom_edge_y && v2.y > bottom_edge_y) {
            new_polygon.push_back(v2);
        }

        // CASE 4 -> Inside To Outside
        if (v1.y > bottom_edge_y && v2.y <= bottom_edge_y) {
            int x, y;
            if (v1.x == v2.x) {
                y = bottom_edge_y;
                x = v1.x;
            } else {
                // Find intersection (x, y)
                double slope = (double) (v1.y - v2.y) / (v1.x - v2.x);
                y = bottom_edge_y;
                x = (int) (v1.x + (1 / slope ) * (bottom_edge_y - v1.y));
            }
            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
        }
    }

    polygon = new_polygon;
}

void clip_top_edge() {
    vector<Point> new_polygon;
    int n = (int) polygon.size();
    for (int i=0; i<n; i++) {
        Point v1 = polygon[i];
        Point v2 = polygon[(i + 1) % n];

        int top_edge_y = clip_window[2][1];

        // Check y coordinates

        // CASE 1 -> Outside to Inside
        if (v1.y >= top_edge_y && v2.y < top_edge_y) {
            int x, y;
            // Find intersection (x, y)
            if (v1.x == v2.x) {
                y = top_edge_y;
                x = v1.x;
            } else {
                double slope = (double) (v1.y - v2.y) / (v1.x - v2.x);
                y = top_edge_y;
                x = (int) (v1.x + (1 / slope) * (top_edge_y - v1.y));
            }
            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
            new_polygon.push_back(v2);
        }

        // CASE 2 -> Both outside (Leave)

        // CASE 3 -> Both inside
        if (v1.y < top_edge_y && v2.y < top_edge_y) {
            new_polygon.push_back(v2);
        }

        // CASE 4 -> Inside To Outside
        if (v1.y < top_edge_y && v2.y >= top_edge_y) {
            int x, y;
            if (v1.x == v2.x) {
                y = top_edge_y;
                x = v1.x;
            } else {
                // Find intersection (x, y)
                double slope = (double) (v1.y - v2.y) / (v1.x - v2.x);
                y = top_edge_y;
                x = (int) (v1.x + (1 / slope )* (top_edge_y - v1.y));
            }
            Point v1_dash; v1_dash.x = x, v1_dash.y = y;
            new_polygon.push_back(v1_dash);
        }
    }

    polygon = new_polygon;
}

void calc_polygon() {
    clip_left_edge();
    clip_right_edge();
    clip_bottom_edge();
    clip_top_edge();
}

void draw_window() {
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    for (int i=0; i<4; i++) {
        glVertex2iv(clip_window[i]);
    }
    glEnd();
}

void draw_polygon() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i=0; i<polygon.size(); i++) {
        glVertex2f(polygon[i].x, polygon[i].y);
    }
    glEnd();
}

void draw_clipped_polygon() {
    calc_polygon();
    draw_polygon();
}

void display() {
    draw_window();
    setup_polygon();
    draw_polygon();
    glFlush();
}

void display2() {
    draw_window();
    draw_clipped_polygon();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Polygon!");
    myInit();
    glutDisplayFunc(display);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(650, 0);
    glutCreateWindow("Polygon Clipped!");
    myInit();
    glutDisplayFunc(display2);

    glutMainLoop();
    return 0;
}