#include <math.h>
#include<stdlib.h>
#include <gl/glut.h> 
#include <iostream>
using namespace std;

float sunr = 0,
planetR = 0,
planetr = 0,
moonR = 0,
moonr = 0;
float day = 0;
float speed = 1;
int rotX = 0, rotY = 0, rotZ = 0;
float  TraX = 0, TraY = 0, TraZ = -10;
double sR = 0.5,
Lsp = 2,
pR = 0.3,
Lpm = 0.6,
mR = 0.15;
void Init_Position() {
	sunr = 0; planetR = 0; planetr = 0; moonR = 0; moonr = 0; day = 0;
}
void Init_Speed() {
	speed = 1;
}
void Init_Rot() {
	rotX = rotY = rotZ = 0;
}
void Init_Tra() {
	TraX = 0; TraY = 0; TraZ = -10;
}
void Init_Light() {
	float r = 0.5;
	float pos[][4] = {
		{r, 0, 0, 1},
		{ -r, 0, 0, 1},
		{0, r, 0, 1},
		{0, -r, 0, 1},
		{0, 0, r, 1},
		{0, 0, -r, 1}
	};
	float diffuse[] = { 0.9f, 0.9f, 0.9f, 1 };
	for (int i = 0; i < 6; ++i)
	{
		glLightfv(GL_LIGHT0 + i, GL_POSITION, pos[i]); // i号光源位置       
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse);       // 第i号光源漫反射成分      
		glEnable(GL_LIGHT0 + i); // 启用i号光源    
	}
	glEnable(GL_LIGHTING);
}
void Init() {
	Init_Light();
	Init_Position();
	Init_Speed();
	Init_Rot();
	Init_Tra();
}

void Reshape(int w, int h) // 窗口变化回调函数 
{
	glViewport(0, 0, w, h); // 视口的位置和大小    
	glMatrixMode(GL_PROJECTION); // 当前变换类型为投影变换   
	glLoadIdentity(); // 当前矩阵为单位矩阵   
	gluPerspective(30, (float)w / h, 1, 1000);    // 定义投影矩阵，参数为：y向张角；x/y；近平面；远平面   
	glTranslatef(TraX, TraY, TraZ); // 适当远移   
	//glRotatef(30, 1, 0, 0); // 调整观察角度   
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotZ, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW); // 当前变换类型为视图造型变换   
	glLoadIdentity();
}

void Timer(int millis) // 定时器回调函数 
{
	float dsunr, dplanetR, dplanetr, dmoonR, dmoonr, dhour = 1.0;
	dsunr = 360 * speed * dhour / (27.5*24.0);
	dplanetR = 360 * speed * dhour / (365.2425*24.0);
	dplanetr = 360 * speed * dhour / 24.0;
	dmoonR = dmoonr = 360 * speed*dhour / (29.5*24.0); sunr = fmod(sunr + dsunr, 360);
	planetR = fmod(planetR + dplanetR, 360);
	planetr = fmod(planetr + dplanetr, 360);
	moonR = fmod(dmoonR + moonR, 360);
	moonr = fmod(dmoonr + moonr, 360);

	if (((int)day + 1) <= (day + speed*dhour / 24.0))
		cout << "day　：" << (int)(day + 0.5) << endl;
	day = fmod((day + speed*dhour / 24.0), 365);

	glutPostRedisplay(); // 调用场景绘制函数    
	glutTimerFunc(millis, Timer, millis);    // 指定定时器函数，参数为：间隔毫秒数，函数名，函数参数值 
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
	case 'Z':
	case 'z':
		rotX = 90; rotY = -18; rotZ = 17;
		break;
	case 'X':
	case 'x':
		rotX = 0; rotY = 0; rotZ = 17;
		break;
	default:
		break;
	}
	cout << "rotX" << rotX << " "
		<< "rotY:" << rotY << " "
		<< "rotZ:" << rotZ << endl;
	Reshape(w, h);
}
void processSpecialKeys(int key, int x, int y)
{
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	switch (key)
	{
	case GLUT_KEY_F1:
		speed *= 2;
		break;
	case GLUT_KEY_F2:
		speed /= 2;
		break;
	case GLUT_KEY_F3:
		Init_Position();
		break;
	case GLUT_KEY_F4:
		Init();
		Reshape(w, h);
		break;
	case GLUT_KEY_LEFT:
		TraX += 0.1;
		Reshape(w, h);
		break;
	case GLUT_KEY_RIGHT:
		TraX -= 0.1;
		Reshape(w, h);
		break;
	case GLUT_KEY_UP:
		TraY -= 0.1;
		Reshape(w, h);
		break;
	case GLUT_KEY_DOWN:
		TraY += 0.1;
		Reshape(w, h);
		break;
	default:
		break;
	}
	cout << "speed:" << speed << " "
		<< "TraX:" << TraX << " "
		<< "TraY:" << TraY << " "
		<< "TraZ:" << TraZ << endl;
}
void Mouse(int button, int state, int x, int y)
{
	GLsizei w = glutGet(GLUT_WINDOW_WIDTH);
	GLsizei h = glutGet(GLUT_WINDOW_HEIGHT);
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			TraZ += 0.5;
			Reshape(w, h);
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			TraZ -= 0.5;
			Reshape(w, h);
		}
		cout << "speed:" << speed << " "
			<< "TraX:" << TraX << " "
			<< "TraY:" << TraY << " "
			<< "TraZ:" << TraZ << endl;
	}
	return;
}
void Diffuse(float r, float g, float b) // 使用颜色指定不发光物体表面材质 
{
	float diffuse[] = { r, g, b, 1 };
	float emission[] = { 0, 0, 0, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); // 反射材质    
	glMaterialfv(GL_FRONT, GL_EMISSION, emission); // 不发光 
}
void Emission(float r, float g, float b) // 使用颜色指定发光物体表面材质 
{
	float diffuse[] = { 0, 0, 0, 1 };
	float emission[] = { r, g, b, 1 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission); // 发光强度   
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); // 不反射
}
void TexImage(float r, float g, float b) // 创建纹理图像数据 
{  // 定义一个一维纹理数据，保持红色、蓝色分量255(MAX)，   
   // 所以是渐变的紫色纹理，饱和度不断变化。   
	enum { TEXTUREWIDTH = 64 }; // 纹理图像宽度   
	GLubyte Texture[TEXTUREWIDTH][3]; // 纹理图像数据   
	for (int i = 0; i < TEXTUREWIDTH; ++i) {
		if (!(i % 9))
			Texture[i][0] = (int)(255 * r), Texture[i][1] = (int)(255 * g), Texture[i][2] = (int)(255 * b);
		else
			Texture[i][0] = 255, Texture[i][1] = 255, Texture[i][2] = 255;
	}
	glTexImage1D(GL_TEXTURE_1D, 0, 3, TEXTUREWIDTH, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture);
	// 定义一维纹理，参数含义依次为：目标纹理，分辨率级别，    
	// 颜色分量数目，宽度，边界宽度，像素数据格式，    
	// 像素数据类型，图像数据
}
void Texture(float r, float g, float b) // 创建并启用纹理 
{
	float plane[] = { 0, 0, 1, 0 };
	TexImage(r, g, b); // 创建纹理图像数据    
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 放大滤波，用z坐标靠近像素中心的4个纹理元素进行线性插值   
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 缩小滤波，用z坐标靠近像素中心的4个纹理元素进行线性插值   
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	// 使用GL_OBJECT_LINEAR对应的函数自动产生纹理的S坐标   
	glTexGenfv(GL_S, GL_OBJECT_PLANE, plane);
	// 使用系数为{1,1,1,0}的函数自动产生纹理的S坐标   
	glEnable(GL_TEXTURE_1D); // 启用一维纹理    
	glEnable(GL_TEXTURE_GEN_S); // 启用纹理S坐标自动产生    
}
void makeaxes(float r) {
	glBegin(GL_LINES);
	Emission(1, 1, 1);
	glVertex3f(0, 0, -r - 0.2);
	glVertex3f(0, 0, r + 0.2);
	glEnd();
}
void makeequator(float r) {
	double PI = 3.1415926;
	int n = 1000;
	Emission(1, 1, 1);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < n; ++i)
		glVertex3d(r*cos(2 * PI / n*i), r*sin(2 * PI / n*i), 0);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
}
void Wire(float r) {
	Emission(1, 1, 1);
	glutWireSphere(r*1.004, 20, 20);
}
void makaobject(float r) {
	Emission(1, 0, 1);
	glTranslatef(-r, 0, 0);
	Texture(1, 0, 0);
	glutSolidCube(0.05);
	glDisable(GL_TEXTURE_1D);
}
void MakeSun(float r) {
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(17, 0, 1, 0);
	glRotated(sunr, 0, 0, 1);
	makeaxes(r);
	Emission(1, 0.01, 0.01);
	Texture(0.8, 0, 0);
	glutSolidSphere(r, 100, 100);
	glDisable(GL_TEXTURE_1D);
	makeequator(r);
	makaobject(r);
	glPopMatrix();
}
void MakePlanet(float r) {
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(planetr, 0, 0, 1);
	makeaxes(r);
	Diffuse(0.1, 0.1, 1);
	Texture(0.1, 1, 1);
	glutSolidSphere(r, 100, 100);
	glDisable(GL_TEXTURE_1D);
	makeequator(r);
	makaobject(r);
	glPopMatrix();
}
void MakeMoom(float r) {
	glPushMatrix();
	glRotated(-90, 1, 0, 0);
	glRotated(moonr, 0, 0, 1);
	makeaxes(r);
	Diffuse(0.5, 0.5, 0.5);
	Texture(1, 1, 0);
	glutSolidSphere(r, 100, 100);
	glDisable(GL_TEXTURE_1D);
	makeequator(r);
	makaobject(r);
	glPopMatrix();
}

void Paint() // 场景绘制函数 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // 清除颜色缓存和深度缓存   
	glLoadIdentity();    // 地球：黄赤角-->位置-->公转    // 月亮：位置--公转-->地球黄赤角   
	glPushMatrix();
	MakeSun(sR);
	glRotated(planetR, 0, 1, 0);
	glTranslatef(Lsp, 0, 0);
	glRotated(-planetR, 0, 1, 0);
	glRotated(-23.5, 0, 0, 1);
	MakePlanet(pR);
	glRotated(moonR, 0, 1, 0);
	glTranslatef(Lpm, 0, 0);
	glRotated(-moonR, 0, 1, 0);

	MakeMoom(mR);
	glPopMatrix();
	//	glEnable(GL_COLOR_MATERIAL);
	glutSwapBuffers(); // 交换颜色缓存 
}
int main() {
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);    // 显示模式为：双缓冲区，RGBA颜色模式  
	glutInitWindowSize(1000, 500);
	glutCreateWindow("日地月系统"); // 窗口标题  
	Init();
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(Mouse);
	//glutFullScreen(); // 使用全屏幕窗口   
	glutTimerFunc(20, Timer, 20);    // 指定定时器函数，参数为：间隔毫秒数，函数名，函数参数值  
	glutReshapeFunc(Reshape); // 指定窗口变化回调函数   
	glutDisplayFunc(Paint); // 指定场景绘制函数    
	glEnable(GL_DEPTH_TEST); // 打开深度测试，用于比较远近  
	glutMainLoop(); // 开始循环执行OpenGL命令 
}