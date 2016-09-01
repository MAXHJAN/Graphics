#include<GL/glut.h>
#include<iostream>
using namespace std;
double oP1[2] = { -0.4,0.8 }, oP2[2] = { 0.8,-0.4 };
double P1[2], P2[2];
double area[2][2] = { {0.0,0.0},{0.8,0.8} };

void setcode(double *P, bool *code) {
	if (P[0] < area[0][0]) {
		code[3] = 1;
	}
	else if (P[0] > area[1][0]) {
		code[2] = 1;
	}
	if (P[1] < area[0][1]) {
		code[1] = 1;
	}
	else if (P[1] > area[1][1]) {
		code[0] = 1;
	}
	cout << "P£®" << P[0] << "£¨" << P[1] << "£© code : " << code[0] << code[1] << code[2] << code[3] << endl;
}
bool Cohen_Sutherland() {
	bool flag = 0;
	bool P1code[4] = { 0,0,0,0 }, P2code[4] = { 0,0,0,0 };
	double m = (oP2[1] - oP1[1]) / (oP2[0] - oP1[0]);
	double x, y;
	setcode(oP1, P1code);
	setcode(oP2, P2code);
	if (P1code[2] != 1) {
		if (!(P1code[3] || P1code[1] || P1code[0])) {
			flag = 1;
			P1[0] = oP1[0]; P1[1] = oP1[1];
		}
		if (flag != 1 && P1code[3] == 1) {
			y = oP1[1] + m*(area[0][0] - oP1[0]);
			if (y >= area[0][1] && y <= area[1][1]) {
				flag = 1;
				P1[0] = area[0][0]; P1[1] = y;
			}
		}
		if (flag != 1 && P1code[1] == 1) {
			x = oP1[0] + (area[0][1] - oP1[1]) / m;
			if (x >= area[0][0] && x <= area[1][0]) {
				flag = 1;
				P1[0] = x; P1[1] = area[1][1];
			}
		}
		if (flag != 1 && P1code[0] == 1) {
			x = oP1[0] + (area[1][1] - oP1[1]) / m;
			if (x >= area[0][0] && x <= area[1][0]) {
				flag = 1;
				P1[0] = x; P1[1] = area[1][1];
			}
		}
	}
	if (flag == 0)
		return flag;
	else
		flag = 0;
	if (P2code[3] != 1) {
		if (!(P2code[2] || P2code[1] || P2code[0])) {
			flag = 1;
			P2[0] = oP2[0]; P2[1] = oP2[1];
		}
		if (flag != 1 && P2code[2] == 1) {
			y = P1[1] + m*(area[1][0] - P1[0]);
			if (y >= area[0][1] && y <= area[1][1]) {
				flag = 1;
				P2[0] = area[1][0]; P2[1] = y;
			}
		}
		if (flag != 1 && P2code[1] == 1) {
			x = P1[0] + (area[0][1] - P1[1]) / m;
			if (x >= area[0][0] && x <= area[1][0]) {
				flag = 1;
				P2[0] = x; P2[1] = area[0][1];
			}
		}
		if (flag != 1 && P2code[0] == 1) {
			x = P1[0] + (area[1][1] - P1[1]) / m;
			if (x >= area[0][0] && x <= area[1][0]) {
				flag = 1;
				P2[0] = x; P2[1] = area[1][1];
			}
		}
	}
	cout << "P1'(" << P1[0] << "," << P1[1] << ")" << endl;
	cout << "P2'(" << P2[0] << "," << P2[1] << ")" << endl;
	return flag;
}
void originLines() {
	glLineWidth(2.5);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2d(oP1[0], oP1[1]);
	glVertex2d(oP2[0], oP2[1]);
	glEnd();
}
void Area() {
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2d(area[0][0], area[0][1]);
	glVertex2d(area[1][0], area[0][1]);
	glVertex2d(area[1][0], area[1][1]);
	glVertex2d(area[0][0], area[1][1]);
	glEnd();
}
void Lines() {
	if (Cohen_Sutherland()) {
		glLineWidth(2.5);
		//glDisable(GL_LINE_SMOOTH);
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2d(P1[0], P1[1]);
		glVertex2d(P2[0], P2[1]);
		glEnd();
	}
}
void Ortho2D(double a) {
	a = a < 0 ? -a : a;
	gluOrtho2D(-a, a, -a, a);
}
void Paint() {
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	Ortho2D(1);
	glViewport(0, 0, w > h ? h : w, w > h ? h : w);
	originLines();
	Lines();
	Area();
	glFlush();
}
int main() {
	glutInitWindowSize(400, 400);
	glutCreateWindow("Cohen-SutherlandÀ„∑®");
	glutDisplayFunc(Paint);
	glutMainLoop();
}