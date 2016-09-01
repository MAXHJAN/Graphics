#include<GL/glut.h>
#include<iostream>
using namespace std;
int ** zdhx(int &lenth, int xl, int yl, int xr, int yr) {
	int **arr;
	int dx = xr - xl, dy = yr - yl;
	int a, b, p, i;
	double m = (double)dy / dx;
	if (m >= 0 && m <= 1) {
		a = -dy; b = dx; p = 0;
		lenth = dx + 1;
		arr = new int *[lenth];
		arr[0] = new int[2];
		arr[0][0] = xl; arr[0][1] = yl; p = 2 * a + b;
		for (i = 1; i < lenth; i++) {
			cout << "(X" << i - 1 << ",Y" << i - 1 << ")=(" << arr[i - 1][0] << "," << arr[i - 1][1] << "), P" << i - 1 << "=" << p << endl;
			arr[i] = new int[2];
			if (p > 0) {
				arr[i][0] = arr[i - 1][0] + 1;
				arr[i][1] = arr[i - 1][1];
			}
			else {
				arr[i][0] = arr[i - 1][0] + 1;
				arr[i][1] = arr[i - 1][1] + 1;
			}
			p = p > 0 ? p + 2 * a : p + 2 * a + 2 * b;
		}
		cout << "(X" << i - 1 << ",Y" << i - 1 << ")=(" << arr[i - 1][0] << "," << arr[i - 1][1] << ")" << endl;
		return arr;
	}
	else if (m >= -1 && m < 0) {
		a = dy; b = dx; p = 0;
		lenth = dx + 1;
		arr = new int *[lenth];
		arr[0] = new int[2];
		arr[0][0] = xl; arr[0][1] = yl; p = 2 * a + b;
		for (i = 1; i < lenth; i++) {
			cout << "(X" << i - 1 << ",-Y" << i - 1 << ")=(" << arr[i - 1][0] << "," << -arr[i - 1][1] << "), P" << i - 1 << "=" << p << endl;
			arr[i] = new int[2];
			if (p > 0) {
				arr[i][0] = arr[i - 1][0] + 1;
				arr[i][1] = arr[i - 1][1];
			}
			else {
				arr[i][0] = arr[i - 1][0] + 1;
				arr[i][1] = -(-arr[i - 1][1] + 1);
			}
			p = p > 0 ? p + 2 * a : p + 2 * a + 2 * b;
		}
		cout << "(X" << i - 1 << ",-Y" << i - 1 << ")=(" << arr[i - 1][0] << "," << -arr[i - 1][1] << ")" << endl;
		return arr;
	}
	else if (m > 1) {
		a = -dx; b = dy; p = 0;
		lenth = dy + 1;
		arr = new int *[lenth];
		arr[0] = new int[2];
		arr[0][0] = xl; arr[0][1] = yl; p = 2 * a + b;
		for (i = 1; i < lenth; i++) {
			cout << "(Y" << i - 1 << ",X" << i - 1 << ")=(" << arr[i - 1][1] << "," << arr[i - 1][0] << "), P" << i - 1 << "=" << p << endl;
			arr[i] = new int[2];
			if (p > 0) {
				arr[i][0] = arr[i - 1][0];
				arr[i][1] = arr[i - 1][1] + 1;
			}
			else {
				arr[i][0] = arr[i - 1][0] + 1;
				arr[i][1] = arr[i - 1][1] + 1;
			}
			p = p > 0 ? p + 2 * a : p + 2 * a + 2 * b;
		}
		cout << "(Y" << i - 1 << ",X" << i - 1 << ")=(" << arr[i - 1][1] << "," << arr[i - 1][0] << ")" << endl;
		return arr;
	}
	else {
		a = -dx; b = -dy; p = 0;
		lenth = -dy + 1;
		arr = new int *[lenth];
		arr[0] = new int[2];
		arr[0][0] = xl; arr[0][1] = yl; p = 2 * a + b;
		for (i = 1; i < lenth; i++) {
			cout << "(-Y" << i - 1 << ",X" << i - 1 << ")=(" << -arr[i - 1][1] << "," << arr[i - 1][0] << "), P" << i - 1 << "=" << p << endl;
			arr[i] = new int[2];
			if (p > 0) {
				arr[i][0] = arr[i - 1][0];
				arr[i][1] = -(-arr[i - 1][1] + 1);
			}
			else {
				arr[i][0] = arr[i - 1][0] + 1;
				arr[i][1] = -(-arr[i - 1][1] + 1);
			}
			p = p > 0 ? p + 2 * a : p + 2 * a + 2 * b;
		}
		cout << "(-Y" << i - 1 << ",X" << i - 1 << ")=(" << -arr[i - 1][1] << "," << arr[i - 1][0] << ")" << endl;
		return arr;
	}
}
void points(int xl, int yl, int xr, int yr) {
	int **arr;
	int lenth;
	arr = zdhx(lenth, xl, yl, xr, yr);
	glBegin(GL_POINTS);
	for (int i = 0; i < lenth; i++) {
		glVertex2i(arr[i][0], arr[i][1]);
		cout << "X" << i << "=" << arr[i][0] << " Y" << i << "=" << arr[i][1] << endl;
	}
	glEnd();
}
void lins(int xl, int yl, int xr, int yr) {
	glBegin(GL_LINES);
	glVertex2i(xl, yl);
	glVertex2i(xr, yr);
	glEnd();
}
void axes(int xl, int yl, int xr, int yr) {
	int temp;
	if (yl > yr) {
		temp = yl;
		yl = yr;
		yr = temp;
	}
	if ((xr - xl) > (yr - yl))
		temp = xr - xl;
	else
		temp = yr - yl;
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0X0F0F);
	for (int x = xl; x <= xl + temp; x++) {
		glBegin(GL_LINES);
		glVertex2i(x, yl);
		glVertex2i(x, yl + temp);
		glEnd();
	}
	for (int y = yl; y <= yl + temp; y++) {
		glBegin(GL_LINES);
		glVertex2i(xl, y);
		glVertex2i(xl + temp, y);
		glEnd();
	}
	glDisable(GL_LINE_STIPPLE);
}
void Ortho2D(int xl, int xr, int yl, int yr) {
	int temp;
	if (yl > yr) {
		temp = yl;
		yl = yr;
		yr = temp;
	}
	if ((xr - xl) > (yr - yl))
		temp = xr - xl;
	else
		temp = yr - yl;
	gluOrtho2D(xl - 0.15, xl + temp + 0.15, yl - 0.15, yl + temp + 0.15);
}
void Paint() {
	int s[2][2] =
		//{ { 20,10 },{ 28,16 } };//0<m<1
	//{ { 20,10 },{ 28,20 } };//m>1
	//{ { 20,10 },{ 28,2 } };//-1<m<0
	{ { 20,10 },{ 28,0 } };//m<-1
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport((w - 400) / 2, (h - 400) / 2, 400, 400);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	Ortho2D(s[0][0], s[1][0], s[0][1], s[1][1]);
	points(s[0][0], s[0][1], s[1][0], s[1][1]);
	lins(s[0][0], s[0][1], s[1][0], s[1][1]);
	axes(s[0][0], s[0][1], s[1][0], s[1][1]);

	/*Ortho2D(0, 31, 0, 31);
	points(0,19,31,19);
	lins(0, 19, 31, 19);
	points(0,19,25,1);
	lins(0, 19, 25, 1);
	points(5,1,15,31);
	lins(5, 1, 15, 31);
	points(5,1,31,19);
	lins(5, 1, 31, 19);
	points(15,31,25,1);
	lins(15, 31, 25, 1);
	axes(0, 0, 31, 31);*/

	glFlush();
}
int main() {
	glutInitWindowSize(420, 420);
	glutCreateWindow("中点画线算法");
	glPointSize(10);
	glutDisplayFunc(Paint);
	glutMainLoop();
}
