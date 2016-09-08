#include<GL/glut.h>
#include <math.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)  
int sign = 4;
float rot = 0;
float sca = 1;
float traX = 0;
bool flag_s = 0;
bool flag_t = 0;
void processSpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		if (sign == 1)
			sign = 0;
		else
			sign = 1;
		break;
	case GLUT_KEY_F2:
		if (sign == 2)
			sign = 0;
		else
			sign = 2;
		break; break;
	case GLUT_KEY_F3:
		if (sign == 3)
			sign = 0;
		else
			sign = 3;
		break; break;
	case GLUT_KEY_F4:
		if (sign == 4)
			sign = 0;
		else
			sign = 4;
		break; break;
	case GLUT_KEY_F5:
		sign = 0;
		rot = 0; sca = 1; traX = 0;
		flag_s = 0; flag_t = 0;
		break;
	default:
		break;
	}
}
void timer(int millis) {
	switch (sign)
	{
	case 4:
	case 3:
		rot += 5;
		if (rot > 360)
			rot -= 360;
		if (sign != 4) break;
	case 2:
		if (flag_s)
			sca += 0.01;
		else
			sca -= 0.01;
		if (sca <= 0) {
			sca = 0; flag_s = 1;
		}
		else if (sca >= 1) {
			sca = 1; flag_s = 0;
		}
		if (sign != 4) break;
	case 1:
		if (flag_t)
			traX -= 0.01;
		else
			traX += 0.01;
		if (traX >= 1) {
			traX = 1; flag_t = 1;
		}
		else if (traX <= -1) {
			traX = -1; flag_t = 0;
		}
		if (sign != 4) break;
	case 0:break;
	default:
		break;
	}
	glutPostRedisplay();
	glutTimerFunc(millis, timer, millis);
}

void Reshape(int w, int h) {
	int min = w > h ? h : w;
	glViewport((w - min) / 2, (h - min) / 2, min, min);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 100);
	glTranslatef(0, 0, -2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void MySolidTetrahedron(double a = 1) {
	static int list = 0;
	if (list == 0)
	{

		GLfloat
			PointA[] = { 0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointB[] = { -0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointC[] = { 0.0f, -sqrt(6.0f) / 12, sqrt(3.0f) / 3 },
			PointD[] = { 0.0f, sqrt(6.0f) / 4, 0 };

		GLfloat

			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };

		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		// 平面ABC 
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorR, PointB);
		ColoredVertex(ColorR, PointC);
		// 平面ACD
		ColoredVertex(ColorB, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorB, PointD);
		// 平面CBD 
		ColoredVertex(ColorY, PointC);
		ColoredVertex(ColorY, PointB);
		ColoredVertex(ColorY, PointD);
		// 平面BAD 
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorG, PointA);
		ColoredVertex(ColorG, PointD);
		glEnd();
		glEndList();
		glEnable(GL_DEPTH_TEST);

	}
	glCallList(list);
}

void axesXYZ() {
	glPushMatrix();
	glBegin(GL_LINES);

	glColor3f(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(10, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 10, 0);

	glColor3f(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 10);

	glPopMatrix();
	glEnd();
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//axesXYZ();
	glPushMatrix();
	glTranslatef(traX, traX, 0);
	glScaled(sca, sca, sca);
	glRotated(rot, 1, 0.5, 0);
	MySolidTetrahedron();
	glPushMatrix();
	glutSwapBuffers();
}
int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("MyTetrahedron");
	glutReshapeFunc(Reshape);
	glutTimerFunc(25, timer, 25);
	glutSpecialFunc(processSpecialKeys);
	glutDisplayFunc(display);
	glutMainLoop();
}