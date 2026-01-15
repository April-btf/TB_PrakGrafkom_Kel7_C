#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>

// ================= CAMERA =================
float camX=0, camY=15, camZ=30;
float rotX=180, rotY=0;
int lastX,lastY;

// ================= STATE =================
bool lampOn=true;
float kursiRotation = 0.0f; // VARIABEL BARU UNTUK ROTASI KURSI

// ================= OBJEK =================
float fridgeX=-25, fridgeY=12, fridgeZ=-25;
float lightPos[]={0,35,0,1};

// ================= batas ruangan =================
float roomMinX = -42, roomMaxX = 42;
float roomMinZ = -42, roomMaxZ = 42;

// ===== AREA MEJA + KURSI (ZONA TERLARANG) =====
float mejaMinX = -18, mejaMaxX = 18;
float mejaMinZ = -18, mejaMaxZ = 18;

// ================= GLOBAL =================
bool lightingEnabled = true;
float teapotScale = 1.0f;   // KONTROL UKURAN TEAPOT
float teapotX = -2.0f;      // POSISI X TEAPOT
float teapotY = 11.1f;      // POSISI Y TEAPOT
float teapotZ = 0.0f;       // POSISI Z TEAPOT

// ================= LANTAI =================
void lantai(){
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glVertex3f( 50,0, 50);
    glVertex3f( 50,0,-50);
    glVertex3f(-50,0,-50);
    glVertex3f(-50,0, 50);
    glEnd();
}

// ================= DINDING =================
void dinding(){
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.55f, 0.0f);

    // kiri
    glNormal3f(1,0,0);
    glVertex3f(-50,0,-50);
    glVertex3f(-50,50,-50);
    glVertex3f(-50,50, 50);
    glVertex3f(-50,0, 50);

    // kanan
    glNormal3f(-1,0,0);
    glVertex3f(50,0, 50);
    glVertex3f(50,50, 50);
    glVertex3f(50,50,-50);
    glVertex3f(50,0,-50);

    // belakang
    glNormal3f(0,0,-1);
    glVertex3f(-50,0,-50);
    glVertex3f( 50,0,-50);
    glVertex3f( 50,50,-50);
    glVertex3f(-50,50,-50);

    // depan + pintu
    glNormal3f(0,0,1);

    glVertex3f(-50,0,50);
    glVertex3f(-10,0,50);
    glVertex3f(-10,50,50);
    glVertex3f(-50,50,50);

    glVertex3f(-10,0,50);
    glVertex3f(10,0,50);
    glVertex3f(10,30,50);
    glVertex3f(-10,30,50);

    glVertex3f(-10,30,50);
    glVertex3f(10,30,50);
    glVertex3f(10,50,50);
    glVertex3f(-10,50,50);

    glVertex3f(10,0,50);
    glVertex3f(50,0,50);
    glVertex3f(50,50,50);
    glVertex3f(10,50,50);

    // plafon
    glColor3f(0.9f,0.9f,0.9f);
    glNormal3f(0,-1,0);
    glVertex3f(-50,50,-50);
    glVertex3f( 50,50,-50);
    glVertex3f( 50,50, 50);
    glVertex3f(-50,50, 50);

    glEnd();
}

// ================= CLAMP CAMERA =================
void clampCamera(){
    if(camX<roomMinX) camX=roomMinX;
    if(camX>roomMaxX) camX=roomMaxX;
    if(camZ<roomMinZ) camZ=roomMinZ;
    if(camZ>roomMaxZ) camZ=roomMaxZ;
    camY=15;
}

// ================= MEJA + TEAPOT ================= (NAJWA)
void meja(){
    glPushMatrix();
    glTranslatef(0,10,0);
    glColor3f(0.6,0.4,0.2);

    glPushMatrix();
    glScalef(12,-1,8);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.4,0.25,0.1);
    for(int x=-1;x<=1;x+=2)
        for(int z=-1;z<=1;z+=2){
            glPushMatrix();
            glTranslatef(x*5,-5,z*3);
            glScalef(1,10,1);
            glutSolidCube(1);
            glPopMatrix();
        }
    glPopMatrix();

    // TEAPOT
    glPushMatrix();
    glTranslatef(teapotX, teapotY, teapotZ);
    glScalef(teapotScale,teapotScale,teapotScale);
    glColor3f(1,0,0);
    glutSolidTeapot(1);
    glPopMatrix();
}

// ================= KURSI ================= (DINDA)
void kursi(float x,float z,float defaultRotation){
    glPushMatrix();
    glTranslatef(x,6,z);
    
    // Menggabungkan rotasi default dengan rotasi input keyboard
    glRotatef(defaultRotation + kursiRotation, 0, 1, 0); 
    
    glScalef(1.2,1.2,1.2);
    glColor3f(0.5,0.3,0.2);

    glPushMatrix();
    glScalef(4,1,4);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,3,-1.5);
    glScalef(4,6,1);
    glutSolidCube(1);
    glPopMatrix();

    for(int i=-1;i<=1;i+=2)
        for(int j=-1;j<=1;j+=2){
            glPushMatrix();
            glTranslatef(i*1.5,-3,j*1.5);
            glScalef(0.5,6,0.5);
            glutSolidCube(1);
            glPopMatrix();
        }
    glPopMatrix();
}

// ================= KULKAS ================= (RANI)
void kulkas(){
    glPushMatrix();
    glTranslatef(fridgeX, fridgeY, fridgeZ);

    glColor3f(0.85,0.85,0.85);
    glPushMatrix();
    glScalef(8,24,8);
    glutSolidCube(1);
    glPopMatrix();

    // pintu atas
    glColor3f(0.9,0.9,0.9);
    glPushMatrix();
    glTranslatef(4.1,6,0);
    glScalef(0.3,10,7.5);
    glutSolidCube(1);
    glPopMatrix();

    // pintu bawah
    glPushMatrix();
    glTranslatef(4.1,-6,0);
    glScalef(0.3,12,7.5);
    glutSolidCube(1);
    glPopMatrix();

    // handle
    glColor3f(0.3,0.3,0.3);
    glPushMatrix();
    glTranslatef(4.4,6,2.5);
    glScalef(0.2,4,0.4);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.4,-6,2.5);
    glScalef(0.2,4,0.4);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

// ================= LAMPU ================= (APRIL)
void lampu(){
    GLUquadric* q = gluNewQuadric();
    gluQuadricNormals(q, GLU_SMOOTH);

    glPushMatrix();
    glTranslatef(0,32,0);

    // kabel
    glColor3f(0.1f,0.1f,0.1f);
    glPushMatrix();
    glTranslatef(0,5,0);
    glScalef(0.15f,10.0f,0.15f);
    glutSolidCube(1);
    glPopMatrix();

    // leher
    glPushMatrix();
    glRotatef(90,1,0,0);
    glColor3f(0.15f,0.15f,0.15f);
    gluCylinder(q, 0.3, 0.3, 0.8, 30, 10);
    glPopMatrix();

    // kap
    glPushMatrix();
    glTranslatef(0,-0.8f,0);
    glRotatef(90,1,0,0);
    glColor3f(0.7f,0.65f,0.5f);
    gluCylinder(q, 0.5, 2.0, 3.0, 50, 40);
    glPopMatrix();

    // bohlam
    glPushMatrix();
    glTranslatef(0,-2.0f,0);
    GLfloat emit[] = {1.0f,1.0f,0.9f,1};
    glMaterialfv(GL_FRONT, GL_EMISSION, emit);
    glColor3f(1,1,0.9);
    glutSolidSphere(0.9,30,30);
    GLfloat noEmit[] = {0,0,0,1};
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmit);
    glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(q);
}

// ================= PINTU =================
void pintu(){
    glPushMatrix();
    glTranslatef(-10,0,49.5);
    glColor3f(0.5,0.3,0.2);
    glBegin(GL_QUADS);
    glVertex3f(0,0,0);
    glVertex3f(20,0,0);
    glVertex3f(20,30,0);
    glVertex3f(0,30,0);
    glEnd();
    glPopMatrix();
}

// PAPAN FOTO
void drawPhotoBoard() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(-50.0f, 5.0f, 0.0f); 
    glRotatef(90, 0, 1, 0); 

    float width = 12.0f;
    float height = 18.0f;

    glColor3f(0.20f, 0.15f, 0.10f);
    glBegin(GL_QUADS);
    glVertex3f(-width/2, 0.0f, 0);
    glVertex3f( width/2, 0.0f, 0);
    glVertex3f( width/2, height, 0);
    glVertex3f(-width/2, height, 0);
    glEnd();

    glColor3f(0.97f, 0.97f, 0.96f);
    glBegin(GL_QUADS);
    glVertex3f(-width/2 + 0.5f, 0.5f, 0.01f);
    glVertex3f( width/2 - 0.5f, 0.5f, 0.01f);
    glVertex3f( width/2 - 0.5f, height - 0.5f, 0.01f);
    glVertex3f(-width/2 + 0.5f, height - 0.5f, 0.01f);
    glEnd();

    int rows = 3; int cols = 2;
    float boxW = (width - 1.0f) / cols;
    float boxH = (height - 1.0f) / rows;
    float startX = -width/2 + 0.5f;
    float startY = height - 0.5f;

    for(int r=0; r<rows; r++){
        for(int c=0; c<cols; c++){
            float px = startX + c*boxW;
            float py = startY - r*boxH;
            glColor3f(0.8f + 0.05f*(r%3), 0.7f + 0.05f*(c%3), 0.6f + 0.05f*((r+c)%3));
            glBegin(GL_QUADS);
            glVertex3f(px, py, 0.02f);
            glVertex3f(px+boxW, py, 0.02f);
            glVertex3f(px+boxW, py-boxH, 0.02f);
            glVertex3f(px, py-boxH, 0.02f);
            glEnd();
        }
    }
    glPopMatrix();
    if (lightingEnabled) glEnable(GL_LIGHTING);
}

// ================= DISPLAY =================
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(-rotY,1,0,0);
    glRotatef(-rotX,0,1,0);
    glTranslatef(-camX,-camY,-camZ);

    if(lampOn){
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    }else{
        glDisable(GL_LIGHT0);
    }

    lantai();
    dinding();
    meja();
    kulkas();
    pintu();
    drawPhotoBoard();
    lampu();

    // Render kursi dengan rotasi dinamis
    kursi(0,-6,0);
    kursi(0,6,180);
    kursi(-10,0,90);
    kursi(10,0,-90);

    glutSwapBuffers();
}

// ================= KEYBOARD =================
void keyboard(unsigned char k,int,int){
    float moveSpeed = 2.0f;
    float rad = rotX * M_PI / 180.0f;
    float dirX = sin(rad);
    float dirZ = cos(rad);

    if(k=='s'){ camX += dirX*moveSpeed; camZ += dirZ*moveSpeed; }
    if(k=='w'){ camX -= dirX*moveSpeed; camZ -= dirZ*moveSpeed; }
    if(k=='a'){ camX -= dirZ*moveSpeed; camZ += dirX*moveSpeed; }
    if(k=='d'){ camX += dirZ*moveSpeed; camZ -= dirX*moveSpeed; }
    
    if(k=='x') teapotScale+=0.1f;
    if(k=='y'){
        teapotScale-=0.1f;
        if(teapotScale<0.2f) teapotScale=0.2f;
    }

    // --- KONTROL ROTASI KURSI ---
    if(k=='r' || k=='R') kursiRotation += 5.0f; // Putar Kanan
    if(k=='e' || k=='E') kursiRotation -= 5.0f; // Putar Kiri

    // --- KONTROL GERAKAN TEAPOT ---
    float teapotMoveSpeed = 0.5f;
    if(k=='c') teapotY += teapotMoveSpeed; // Atas
    if(k=='f') teapotY -= teapotMoveSpeed; // Bawah
    if(k=='g') teapotZ += teapotMoveSpeed; // Depan (Z positif)
    if(k=='t') teapotZ -= teapotMoveSpeed; // Belakang (Z negatif)

    clampCamera();

    float f=2.0f;
    float oldFridgeX = fridgeX, oldFridgeZ = fridgeZ;
    if(k=='l') fridgeZ -= f;
    if(k=='j') fridgeZ += f;
    if(k=='k') fridgeX -= f;
    if(k=='i') fridgeX += f;

    fridgeX = fmax(roomMinX, fmin(roomMaxX, fridgeX));
    fridgeZ = fmax(roomMinZ, fmin(roomMaxZ, fridgeZ));

    if(fridgeX > mejaMinX && fridgeX < mejaMaxX &&
       fridgeZ > mejaMinZ && fridgeZ < mejaMaxZ){
        fridgeX = oldFridgeX; fridgeZ = oldFridgeZ;
    }

    if(k=='o') lampOn=!lampOn;

    glutPostRedisplay();
}

// ================= MOUSE =================
void mouse(int b,int s,int x,int y){
    if(b==GLUT_LEFT_BUTTON && s==GLUT_DOWN){ lastX=x; lastY=y; }
}

void motion(int x,int y){
    rotX += (x-lastX)*0.3f;
    rotY += (y-lastY)*0.3f;
    lastX=x; lastY=y;
    glutPostRedisplay();
}

// ================= RESHAPE =================
void reshape(int w,int h){
    if(h==0) h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,(float)w/h,1,500);
    glMatrixMode(GL_MODELVIEW);
}

// ================= MAIN =================
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1024,768);
    glutCreateWindow("Ruang Makan");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();
    return 0;
}
