#include<GL/glut.h>
#include<iostream>
using namespace std;

int rotX = 0, rotY = 0, rotZ = 0;
float  TraX = 0, TraY = 0, TraZ = -1.5;
void Init_Rot() {
	rotX = rotY = rotZ = 0;
	TraX = 0, TraY = 0, TraZ = -1.5;
}
void Init_Light() {
	float pos[] = { 0,0,1,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
void Init() {
	Init_Rot();
	Init_Light();
}
void  Reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (double)w / h, 1, 100);
	glTranslatef(TraX, TraY, TraZ); // 适当远移   
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Keyboard(GLubyte key, GLint x, GLint y) // 键盘按键响应函数 
{
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	switch (key)
	{
	case 27:
		exit(0);
	case 'W':
	case 'w':
		rotX = (rotX + 1) % 360;
		break;
	case 'S':
	case 's':
		rotX = (rotX - 1 + 360) % 360;
		break;
	case 'A':
	case 'a':
		rotY = (rotY + 1) % 360;
		break;
	case 'D':
	case 'd':
		rotY = (rotY - 1 + 360) % 360;
		break;
	case 'Q':
	case 'q':
		Init_Rot();
		break;
	case 'J':
	case 'j':
		rotZ = (rotZ + 1) % 360;
		break;
	case 'K':
	case 'k':
		rotZ = (rotZ - 1 + 360) % 360;
		break;
	default:
		break;
	}
	cout << "rotX" << rotX << " "
		<< "rotY:" << rotY << " "
		<< "rotZ:" << rotZ << endl;
	Reshape(w, h);
	glutPostRedisplay();
}
void processSpecialKeys(int key, int x, int y)
{
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	switch (key)
	{
	case GLUT_KEY_LEFT:
		TraX += 0.1;
		break;
	case GLUT_KEY_RIGHT:
		TraX -= 0.1;
		break;
	case GLUT_KEY_UP:
		TraY -= 0.1;
		break;
	case GLUT_KEY_DOWN:
		TraY += 0.1;
		break;
	default:
		break;
	}
	cout << "TraX:" << TraX << " "
		<< "TraY:" << TraY << " "
		<< "TraZ:" << TraZ << endl;
	Reshape(w, h);
	glutPostRedisplay();
}
void Mouse(int button, int state, int x, int y)
{
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
			TraZ += 0.1;
		else if (button == GLUT_RIGHT_BUTTON)
			TraZ -= 0.1;
		cout << "TraX:" << TraX << " "
			<< "TraY:" << TraY << " "
			<< "TraZ:" << TraZ << endl;
		Reshape(w, h);
		glutPostRedisplay();
	}
	return;
}
void makecube0() {
	glPushMatrix();
	glColor3f(1, 0, 0);
	glScaled(0.6, 0.2, 0.2);
	//glutWireCube(1);
	glutSolidCube(1);
	glPopMatrix();
}
void makecube1() {
	glPushMatrix();
	glColor3f(0, 0, 1);
	glScaled(0.8, 0.2, 0.2);
	glTranslated(0, 0.5, -0.6);
	//glutWireCube(1);
	glutSolidCube(1);
	glPopMatrix();
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

	glEnd();

	glPopMatrix();
}
void Paint() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glEnable(GL_COLOR_MATERIAL);
	axesXYZ();
	static int list = 0;
	if (list == 0)
	{

		GLfloat

			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };

		list = glGenLists(1);
		glNewList(list, GL_COMPILE);

		makecube1();
		makecube0();

		glEndList();
		glEnable(GL_DEPTH_TEST);

	}
	glCallList(list);

	glutSwapBuffers();
}
int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400, 400);
	glutCreateWindow("透视变换");

	Init();
	glutKeyboardFunc(Keyboard); 
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(Mouse);

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Paint);

	glutMainLoop();
}