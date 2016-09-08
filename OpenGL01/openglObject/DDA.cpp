#include<GL/glut.h>
#include<iostream>
using namespace std;
double ** dda(int &lenth, int xl, int yl, int xr, int yr) {
	double **arr;
	int dx = xr - xl, dy = yr - yl;
	double m = (double)dy / dx;
	if (m < -1 || m>1) {
		lenth = dy;
		if (lenth < 0) 
			lenth = -lenth;
		lenth++;
		arr = new double *[lenth];
		arr[0] = new double[2]; arr[0][0] = xl; arr[0][1] = yl;
		for (int i = 1; i < lenth; i++) {
			arr[i] = new double[2];
			if (m > 0) {
				arr[i][0] = arr[i - 1][0] + 1 / m;
				arr[i][1] = arr[i - 1][1] + 1;
			}
			else {
				arr[i][0] = arr[i - 1][0] - 1 / m;
				arr[i][1] = arr[i - 1][1] - 1;
			}
		}
		return arr;
	}
	else {
		lenth = dx + 1;
		arr = new double *[lenth];
		arr[0] = new double[2]; arr[0][0] = xl; arr[0][1] = yl;
		for (int i = 1; i < lenth; i++) {
			arr[i] = new double[2];
			arr[i][0] = arr[i - 1][0] + 1;
			arr[i][1] = arr[i - 1][1] + m;

		}
		return arr;
	}
}
void Points(int xl, int yl, int xr, int yr) {
	double **arr;
	int lenth, X, Y;
	arr = dda(lenth, xl, yl, xr, yr);
	glBegin(GL_POINTS);
	for (int i = 0; i < lenth; i++) {
		if (arr[i][0] > 0)
			X = arr[i][0] + 0.5;
		else 
			X = arr[i][0] - 0.5;
		if (arr[i][1] > 0)
			Y = arr[i][1] + 0.5;
		else
			Y = arr[i][1] - 0.5;
		glVertex2i(X, Y);
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
	int points[2][2] ={ { 20,10 },{ 28,16 } };//两个端点
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);//当前窗口宽度
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);//当前窗口高度
	glViewport((w - 400) / 2, (h - 400) / 2, 400, 400);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();// 重置当前指定的矩阵为单位矩阵
	Ortho2D(points[0][0], points[1][0], points[0][1], points[1][1]);
	Points(points[0][0], points[0][1], points[1][0], points[1][1]);
	lins(points[0][0], points[0][1], points[1][0], points[1][1]);
	axes(points[0][0], points[0][1], points[1][0], points[1][1]);
	glFlush();
}
int main() {
	glutInitWindowSize(420, 420);
	glutCreateWindow("DDA算法");
	glPointSize(10);
	glutDisplayFunc(Paint);
	glutMainLoop();
}
