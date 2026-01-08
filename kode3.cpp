//List program menggambar objek 1
#include <Gl/glut.h>
#include <GL/glut.h>
void Garis ();
main(int argc, char** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600, 800);
glutInitWindowPosition(900,120);
glutCreateWindow("Latihan 2 - membuat objek banyak titik, dengan variasi warna");
glClearColor(1.0, 1.0, 1.0, 0.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(-300.0, 300.0, -400.0, 400.0);
glutIdleFunc(Garis);
glutDisplayFunc(Garis);
glutMainLoop();
}
void Garis ()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(0,0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2d(300,0);
	glEnd();
	glFinish();
	
}
