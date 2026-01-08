#include <gl/glut.h>

void init(const char *title);
void display ();

int main(int argc, char *argv [])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	init("Code 3 - Rotation");
	glutMainLoop();
	return 0;
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'r':
			glutPostRedisplay();
			break;
	}

}

void init(const char *title)
{
	glutCreateWindow(title);
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
}

void makeCube()
{
	glRecti(-10, -10, 10, 10);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.5);
	glRotatef(15.0, 0, 0, 1.0);
	makeCube();
	glFlush();
}
