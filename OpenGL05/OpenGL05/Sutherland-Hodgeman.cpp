#include<GL/glut.h>
#include<iostream>
using namespace std;
int num = 3;
double A[2] = { -0.1,0 }, B[2] = { 0.1,0.2 }, C[2] = { 0.3,0 };
double P[6][2];
double area[2][2] = { { 0.0,0.1 },{ 0.3,0.3 } };
void setP_toL() {
	double cP[6][2];
	double c = area[0][0];
	double  m, x1, x2, y1, y2, y;
	int l = 0;
	for (int i = 0; i < num; i++) {
		cP[i][0] = P[i][0]; cP[i][1] = P[i][1];
	}
	for (int i = 0; i < num; i++) {
		x1 = cP[i][0]; x2 = cP[(i + 1) % num][0];
		y1 = cP[i][1]; y2 = cP[(i + 1) % num][1];
		if (x1 < c&&x2 >= c) {
			m = (y2 - y1) / (x2 - x1);
			y = y1 + (c - x1)*m;
			P[l][0] = c; P[l++][1] = y;
			P[l][0] = x2; P[l++][1] = y2;
			if (x2 == c&&y2 == y)
				l--;
		}
		else if (x1 >= c&&x2 >= c) {
			P[l][0] = x2; P[l++][1] = y2;
		}
		else if (x1 >= c&&x2 < c) {
			m = (y2 - y1) / (x2 - x1);
			y = y1 + (c - x1)*m;
			P[l][0] = c; P[l++][1] = y;
		}
	}
	num = l;
}
void setP_toR() {
	double cP[6][2];
	double c = area[1][0];
	double  m, x1, x2, y1, y2, y;
	int l = 0;
	for (int i = 0; i < num; i++) {
		cP[i][0] = P[i][0]; cP[i][1] = P[i][1];
	}
	for (int i = 0; i < num; i++) {
		x1 = cP[i][0]; x2 = cP[(i + 1) % num][0];
		y1 = cP[i][1]; y2 = cP[(i + 1) % num][1];
		if (x1 > c&&x2 <= c) {
			m = (y2 - y1) / (x2 - x1);
			y = y1 + (c - x1)*m;
			P[l][0] = c; P[l++][1] = y;
			P[l][0] = x2; P[l++][1] = y2;
			if (x2 == c&&y2 == y)
				l--;
		}
		else if (x1 <= c&&x2 <= c) {
			P[l][0] = x2; P[l++][1] = y2;
		}
		else if (x1 <= c&&x2 > c) {
			m = (y2 - y1) / (x2 - x1);
			y = y1 + (c - x1)*m;
			P[l][0] = c; P[l++][1] = y;
		}
	}
	num = l;
}

void setP_toD() {
	double cP[6][2];
	double c = area[0][1];
	double  m, x1, x2, y1, y2, x;
	int l = 0;
	for (int i = 0; i < num; i++) {
		cP[i][0] = P[i][0]; cP[i][1] = P[i][1];
	}
	for (int i = 0; i < num; i++) {
		x1 = cP[i][0]; x2 = cP[(i + 1) % num][0];
		y1 = cP[i][1]; y2 = cP[(i + 1) % num][1];
		if (y1 < c&&y2 >= c) {
			m = (y2 - y1) / (x2 - x1);
			x = x1 + (c - y1) / m;
			P[l][0] = x; P[l++][1] = c;
			P[l][0] = x2; P[l++][1] = y2;
			if (x2 == x&&y2 == c)
				l--;
		}
		else if (y1 >= c&&y2 >= c) {
			P[l][0] = x2; P[l++][1] = y2;
		}
		else if (y1 >= c&&y2 < c) {
			m = (y2 - y1) / (x2 - x1);
			x = x1 + (c - y1) / m;
			P[l][0] = x; P[l++][1] = c;
		}
	}
	num = l;
}
void setP_toU() {
	double cP[6][2];
	double c = area[1][1];
	double  m, x1, x2, y1, y2, x;
	int l = 0;
	for (int i = 0; i < num; i++) {
		cP[i][0] = P[i][0]; cP[i][1] = P[i][1];
	}
	for (int i = 0; i < num; i++) {
		x1 = cP[i][0]; x2 = cP[(i + 1) % num][0];
		y1 = cP[i][1]; y2 = cP[(i + 1) % num][1];
		if (y1 > c&&y2 <= c) {
			m = (y2 - y1) / (x2 - x1);
			x = x1 + (c - y1) / m;
			P[l][0] = x; P[l++][1] = c;
			P[l][0] = x2; P[l++][1] = y2;
			if (x2 == x&&y2 == c)
				l--;
		}
		else if (y1 <= c&&y2 <= c) {
			P[l][0] = x2; P[l++][1] = y2;
		}
		else if (y1 <= c&&y2 > c) {
			m = (y2 - y1) / (x2 - x1);
			x = x1 + (c - y1) / m;
			P[l][0] = x; P[l++][1] = c;
		}
	}
	num = l;
}
void showP() {
	for (int i = 0; i < num; i++) {
		cout << "P" << i << "(" << P[i][0] << "," << P[i][1] << ")" << endl;
	}
	cout << endl;
}
bool Sutherland_Hodgeman() {

	P[0][0] = A[0]; P[0][1] = A[1];
	P[1][0] = B[0]; P[1][1] = B[1];
	P[2][0] = C[0]; P[2][1] = C[1];
	num = 3;

	setP_toL();
	if (num == 0)
		return 0;
	showP();
	setP_toR();
	if (num == 0)
		return 0;
	showP();
	setP_toD();
	if (num == 0)
		return 0;
	showP();
	setP_toU();
	if (num == 0)
		return 0;
	else {
		showP();
		return 1;
	}
}
void originTriangle() {
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2d(A[0], A[1]);
	glVertex2d(B[0], B[1]);
	glVertex2d(C[0], C[1]);
	glEnd();
}
void Area() {
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 1);
	glVertex2d(area[0][0], area[0][1]);
	glVertex2d(area[1][0], area[0][1]);
	glVertex2d(area[1][0], area[1][1]);
	glVertex2d(area[0][0], area[1][1]);
	glEnd();
}
void Polygon() {
	if (Sutherland_Hodgeman()) {
		glPointSize(3);
		glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
		for (int i = 0; i < num; i++)
			glVertex2d(P[i][0], P[i][1]);
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
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	Ortho2D(0.4);
	glViewport(0, 0, w > h ? h : w, w > h ? h : w);
	originTriangle();
	Polygon();
	Area();
	glFlush();
}
int main() {
	glutInitWindowSize(400, 400);
	glutCreateWindow("Sutherland-HodgemanÀ„∑®");
	glutDisplayFunc(Paint);
	glutMainLoop();
}