#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

int screenWidth = 1920;
int screenHeight = 1080;

// Camera position
float camX = 0.0f;
float camY = 5.0f;
float camZ = 25.0f;

// Look at point (center/target)
float lookX = 0.0f;
float lookY = 0.0f;
float lookZ = 0.0f;

// Movement speed
float moveSpeed = 0.2f;
float zoomSpeed = 0.5f;

float rotationAngle = 0.0;

void grid3D();
void sparkle();
void cartesius();
void doughnut3D(int x, int y, int z);
void block3D(int x, int y, int z, float size_x = 1.0f, float size_y = 1.0f, float size_z = 1.0f);

void drawObject3D() {
    grid3D();
    cartesius();
    block3D(0, 1, 0, 0.2f, 2.5f, 0.2f); 
    block3D(0, 21, 0, 2.5f, 0.25f, 2.5f);
    block3D(0, 20, 0, 1.0f, 0.1f, 1.0f);
    doughnut3D(0, 6, 0);
    sparkle();
}

void grid3D()
{
    glLineWidth(1.0);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    for (int i = -50; i <= 50; i += 1)
    {
        glVertex3f(-50.0, 0.0, i);
        glVertex3f(50.0, 0.0, i);

        glVertex3f(i, 0.0, -50.0);
        glVertex3f(i, 0.0, 50.0);
    }
    glEnd();
}

void cartesius(){
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, -100.0, 0.0);
    glVertex3f(0.0, 100.0, 0.0);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-100.0, 0.0, 0.0);
    glVertex3f(100.0, 0.0, 0.0);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, -100.0);
    glVertex3f(0.0, 0.0, 100.0);
    glEnd();
}

void block3D(int x, int y, int z, float size_x, float size_y, float size_z)
{
    glPushMatrix();
    glScaled(size_x, size_y, size_z);
    glTranslatef(x, y, z);
    glLineWidth(5.0);
    glColor3ub(245, 245, 245);
    glutWireCube(2.0);
    glColor3ub(150, 75, 0) ;
    glutSolidCube(1.98);
    glPopMatrix();
}

void doughnut3D(int x, int y, int z){
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 1.0f, 0.0f, 0.0f); 
    glLineWidth(5.0);
    glColor3ub(245, 245, 245);
    glutWireTorus(0.5, 1.0, 20, 20); 
    glColor3ub(255, 215, 0); 
    glutSolidTorus(0.48, 1.0, 20, 20); 
    glPopMatrix();
}

void sparkle(){
    for (int i = 0; i < 13; ++i)
    {
        float angle = (i * (360.0f / 12) * (PI / 180.0f)) + rotationAngle;
        float x = 2 * cos(angle);
        float z = 2 * sin(angle);

        glPushMatrix();
        glColor3f(0.0f, 1.0f, 1.0f);
        glTranslatef(x, 6.0f, z);
        glScaled(0.2f, 0.2f, 0.2f);
        glutWireTetrahedron();
        glPopMatrix();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);
    drawObject3D();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
    
    rotationAngle += 0.0001;
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 27:  // ESC key - Exit
            exit(0);
            break;
        case '+':
        case '=':  
            camZ -= zoomSpeed;
            break;       
        case '-':
        case '_': 
            camZ += zoomSpeed;
            break;
    }
    glutPostRedisplay();
}

// Special keys untuk arrow keys
void specialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_UP:     
            camY += moveSpeed;
            break;
            
        case GLUT_KEY_DOWN:  
            camY -= moveSpeed;
            break;
            
        case GLUT_KEY_LEFT:  
            camX -= moveSpeed;
            break;
            
        case GLUT_KEY_RIGHT: 
            camX += moveSpeed;
            break;
    }
    glutPostRedisplay();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    screenWidth = w;
    screenHeight = h;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Code 08");
    glutFullScreen();
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys); 
    glutMainLoop();
    return 0;
}
