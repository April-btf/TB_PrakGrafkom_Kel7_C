//List program menggambar objek 1
#include <Gl/glut.h>
#include <GL/glut.h>
void titik ();
main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600, 800);
glutInitWindowPosition(100, 100);
glutCreateWindow("Latihan 1 - membuat objek sebuah titik");
glClearColor(0.0, 0.0, 0.0, 0.0);
glMatrixMode(GL_PROJECTION);
glOrtho(-300.0, 300.0, -400.0, 400.0, 0.0, 0.0);
glutDisplayFunc(titik);
glutMainLoop();
}
void titik ()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(50.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(0,0);
	glEnd();
	glFinish();
	
}
