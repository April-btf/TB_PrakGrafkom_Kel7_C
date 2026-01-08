#include <Math.h>
#include <GL/glut.h>

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 10.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	
}

void display (void)

{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(32, 30, 32);
	float x = 0.0;
	glPointSize (1.5);
	glBegin(GL_POINTS);
	for (x= 0.0; x <= 6.28; x += 0.1)
	
	{
		
	glVertex2f(x, sin(x));
	
	}
	
	glEnd();
	glBegin (GL_LINES);
	glColor3ub(30, 32, 30);
	glVertex3f(-10.0, 0.0, 0.0);
	glVertex3f( 10.0, 0.0, 0.0);
	glVertex3f( 0.0, -10.0, 0.0);
	glVertex3f( 0.0, 10.0, 0.0);
	glEnd();
	glFlush();
	
}

void kunci (unsigned char key, int x, int y)

{
	switch (key)
	
	{
		case 27:
		case 'q':
			exit (0);
			break;
	}
	
	glutPostRedisplay();
	
}

int main (int argc, char *argv [])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Code 3 - Kurva Trinogometri");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
	return 0;
}


