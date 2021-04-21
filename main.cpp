#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
double rotAngle = 0; // rotation angle (BEWARE: Global)
double rotAngle1 = 0; // rotation angle (BEWARE: Global)
float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int bitmapHeight=12;
const double PI = 3.141592653589793;
int i,j,radius,jumlah_titik,x_tengah,y_tengah;

void Reshape(int w1, int h1)
{
// Fungsi reshape
    if(h1 == 0) h1 = 1;
    w = w1;
    h = h1;
    ratio = 1.0f * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45,ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        x, y, z,
        x + lx,y + ly,z + lz,
        0.0f,1.0f,0.0f);
}

void moveMeFlat(int i)
{
// Fungsi ini untuk maju mundur kamera
    x = x + i*(lx)*1;
    z = z + i*(lz)*1;
    glLoadIdentity();
    gluLookAt(x, y, z,x + lx,y + ly,z + lz,0.0f,1.0f,0.0f);
}

void keyboard(unsigned char k, int x, int y)
{
// Fungsi ini untuk rotasi kamera
    switch (k)
    {
    case 'a':
        rotAngle += 10; // increase rotation by 5 degrees
        break;
    case 'w':
        rotAngle1 += 10; // increase rotation by 5 degrees
        break;
    case 's':
        rotAngle1 -= 10; // increase rotation by 5 degrees
        break;
    case 'd':
        rotAngle -= 10; // decrease rotation by 5 degrees
        break;
    case 'q':
        exit(0); // exit
    }
    glutPostRedisplay();
}

void Grid()
{
// Fungsi untuk membuat grid di "lantai"
    double i;
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float gap = 1.5;
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for(i=Z_MIN; i<Z_MAX; i+=gap)
    {
        glVertex3f(i, 0, Z_MIN);
        glVertex3f(i, 0, Z_MAX);
    }
    for(i=X_MIN; i<X_MAX; i+=gap)
    {
        glVertex3f(X_MIN, 0, i);
        glVertex3f(X_MAX, 0, i);
    }
    glEnd();
}

void Truk()
{
    glPushMatrix();
    glTranslatef(-3,0.8,0);
	//---------Kepala truk--------------
	//depan
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor3f(0.9,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,3.0f,0.0f);    
	glVertex3f(0.0f,3.0f,0.0f);
    glVertex3f(-1.0f,1.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //kaca depan
    glPushMatrix();
    glTranslatef(0,0,3.01);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUADS);
	glVertex3f(-0.5f,1.5f,0.0f);
    glVertex3f(1.6f,1.5f,0.0f);
    glVertex3f(1.6f,2.7f,0.0f);    
	glVertex3f(0.25f,2.7f,0.0f);
    
    glEnd();
    glPopMatrix();


 	//atas 
	glPushMatrix(); 
	glRotated(-90, 1, 0, 0); 
	glTranslatef(0,-3,3);
	glRotated(-10, 0, 0, 0);
    glColor3f(0.9,1.0,0.0);
	glBegin(GL_QUADS); 
	glVertex3f(0.0f,0.0f,0.0f); 
	glVertex3f(2.0f,0.0f,0.0f); 
	glVertex3f(2.0f,3.05f,0.0f); 
	glVertex3f(0.0f,3.05f,0.0f); 
	glEnd(); 
	glPopMatrix();

	//belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(0,-1,0);
    glColor3f(0.9,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-1.0f,1.0f,0.0f);
    glVertex3f(2.0f,1.0f,0.0f);
    glVertex3f(2.0f,-2.0f,0.0f);
    glVertex3f(0.0f,-2.0f,0.0f);
    glVertex3f(-1.0f,-0.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(0,-1,0.01);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_POLYGON);
    glVertex3f(1.6f,-0.5f,0.0f);
    glVertex3f(1.6f,-1.7f,0.0f);
    glVertex3f(0.3f,-1.7f,0.0f);
    glVertex3f(-0.5f,-0.5f,0.0f);
    glEnd();
    glPopMatrix();

	//bawah
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0,0,0);
    glColor3f(0.9,1.0,0.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f); // kiri bawah
    glVertex3f(-1.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,0.0f); // kiri bawah
    glVertex3f(2.0f,0.0f,0.0f);
    glTexCoord2f(1.0f,1.0f); // kiri bawah
    glVertex3f(2.0f,3.0f,0.0f);
    glTexCoord2f(0.0f,1.0f); // kiri bawah
    glVertex3f(-1.0f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
    
	//kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,1);
    glColor3f(0.9,1.0,0.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,1.5f,0.0f);
    glVertex3f(-1.0f,1.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,1.5,1);
    glRotated(-34, 1, 0, 0);
    glColor3f(0.9,1.0,0.0);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,1.8f,0.0f);
    glVertex3f(-1.0f,1.8f,0.0f);
    glEnd();
    glPopMatrix();
	
	//kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1.25,1.5,1.01);
    glRotated(-34, 1, 0, 0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(1.5f,0.0f,0.0f);
    glVertex3f(1.5f,1.6f,0.0f);
    glVertex3f(-1.0f,1.6f,0.0f);
    glEnd();
    glPopMatrix();
    
	//---------RODA 1 depan--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(1,0,-0.5);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,3.1);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,2.5);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    //---------RODA 1 belakang--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(1,0,-3.05);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,0.55);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-0.05);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
	//---------BADAN 1--------------
	//---------Bak HITAM 1--------------
	//depan
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.5f,0.0f,0.0f);
    glVertex3f(2.5f,3.5f,0.0f);
    glVertex3f(2.0f,3.5f,0.0f);
    glEnd();
    glPopMatrix();

	//belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(0,0,0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.5f,0.0f,0.0f);
    glVertex3f(2.5f,-3.5f,0.0f);
    glVertex3f(2.0f,-3.5f,0.0f);
    glEnd();
    glPopMatrix();

	//atas
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(0.25,-3,3.5);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(1.75f,0.0f,0.0f);
    glVertex3f(2.25f,0.0f,0.0f);
    glVertex3f(2.25f,3.0f,0.0f);
    glVertex3f(1.75f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
	//kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,-2);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,3.5f,0.0f);
    glVertex3f(-1.0f,3.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //kanan
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,-2.5);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,3.5f,0.0f);
    glVertex3f(-1.0f,3.5f,0.0f);
    glEnd();
    glPopMatrix();
    
	//bawah
    glPushMatrix();
    glRotated(90, 1, 0, 0);
    glTranslatef(0,0,0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.5f,0.0f,0.0f);
    glVertex3f(2.5f,3.0f,0.0f);
    glVertex3f(2.0f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    //---------bak HITAM 2--------------
	//depan
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,0.5f,0.0f);
    glVertex3f(2.0f,0.5f,0.0f);
    glEnd();
    glPopMatrix();

	//belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(0,0,0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,-0.5f,0.0f);
    glVertex3f(2.0f,-0.5f,0.0f);
    glEnd();
    glPopMatrix();

	//atas
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(0.25,-3,3.5);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(1.75f,0.0f,0.0f);
    glVertex3f(2.25f,0.0f,0.0f);
    glVertex3f(2.25f,3.0f,0.0f);
    glVertex3f(1.75f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
	//kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,-2);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,3.5f,0.0f);
    glVertex3f(-1.0f,3.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //kanan
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,-8.5);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.5f,0.0f);
    glVertex3f(-1.0f,0.5f,0.0f);
    glEnd();
    glPopMatrix();
    
	//bawah
    glPushMatrix();
    glRotated(90,1,0,0);
    glTranslatef(0,0,0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,3.0f,0.0f);
    glVertex3f(2.0f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
    
	//---------bak merah--------------
	//depan
    glPushMatrix();
    glTranslatef(0,0,3);
    glColor3f(0.6,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(2.5f,0.5f,0.0f);
    glVertex3f(8.5f,0.5f,0.0f);
    glVertex3f(8.5f,3.0f,0.0f);
    glVertex3f(3.0f,3.0f,0.0f);
    glVertex3f(2.5f,3.5f,0.0f);
    glEnd();
    glPopMatrix();

	//belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(0,0,0);
    glColor3f(0.6,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(2.5f,-0.5f,0.0f);
    glVertex3f(8.5f,-0.5f,0.0f);
    glVertex3f(8.5f,-3.0f,0.0f);
    glVertex3f(3.0f,-3.0f,0.0f);
    glVertex3f(2.5f,-3.5f,0.0f);
    glEnd();
    glPopMatrix();

	//bawah
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(0,-3,1);
    glColor3f(0.6,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex3f(2.5f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,3.0f,0.0f);
    glVertex3f(2.5f,3.0f,0.0f);
    glEnd();
    glPopMatrix();

	//kanan
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(-6.2,0.5,8.5);
    glColor3f(0.6,0.0,0.0);
    glBegin(GL_QUADS);
    glVertex3f(3.2f,0.0f,0.0f);
    glVertex3f(6.2f,0.0f,0.0f);
    glVertex3f(6.2f,1.5f,0.0f);
    glVertex3f(3.2f,1.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //kiri
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,-2.51);
    glColor3f(1.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,3.5f,0.0f);
    glVertex3f(-1.0f,3.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //---------RODA 2 depan--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(7,0,-0.5);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6,0,3.1);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6,0,2.5);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    //---------RODA 2 belakang--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(7,0,-3.05);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6,0,0.55);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6,0,-0.05);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    //---------------- BADAN 2 -------------------
    //---------bak HITAM 2--------------
	//depan
    glPushMatrix();
    glTranslatef(6.5,0,3);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,0.5f,0.0f);
    glVertex3f(2.0f,0.5f,0.0f);
    glEnd();
    glPopMatrix();

	//belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(6.5,0,0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,-0.5f,0.0f);
    glVertex3f(2.0f,-0.5f,0.0f);
    glEnd();
    glPopMatrix();
    
    //kanan
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glTranslatef(1,0,-15);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(2.0f,0.5f,0.0f);
    glVertex3f(-1.0f,0.5f,0.0f);
    glEnd();
    glPopMatrix();
    
	//bawah
    glPushMatrix();
    glRotated(90,1,0,0);
    glTranslatef(6.5,0,0);
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
    glVertex3f(2.0f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,3.0f,0.0f);
    glVertex3f(2.0f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    //---------bak hijau--------------
	//depan
    glPushMatrix();
    glTranslatef(6.5,0,3);
    glColor3f(0.2,1.0,0.2);
    glBegin(GL_POLYGON);
    glVertex3f(2.5f,0.5f,0.0f);
    glVertex3f(8.5f,0.5f,0.0f);
    glVertex3f(8.5f,3.0f,0.0f);
    glVertex3f(3.0f,3.0f,0.0f);
    glVertex3f(2.5f,3.5f,0.0f);
    glEnd();
    glPopMatrix();

	//belakang
    glPushMatrix();
    glRotated(-180, 1, 0, 0);
    glTranslatef(6.5,0,0);
    glColor3f(0.2,1.0,0.2);
    glBegin(GL_POLYGON);
    glVertex3f(2.5f,-0.5f,0.0f);
    glVertex3f(8.5f,-0.5f,0.0f);
    glVertex3f(8.5f,-3.0f,0.0f);
    glVertex3f(3.0f,-3.0f,0.0f);
    glVertex3f(2.5f,-3.5f,0.0f);
    glEnd();
    glPopMatrix();

	//bawah
    glPushMatrix();
    glRotated(-90, 1, 0, 0);
    glTranslatef(6.5,-3,1);
    glColor3f(0.2,1.0,0.2);
    glBegin(GL_QUADS);
    glVertex3f(2.5f,0.0f,0.0f);
    glVertex3f(8.5f,0.0f,0.0f);
    glVertex3f(8.5f,3.0f,0.0f);
    glVertex3f(2.5f,3.0f,0.0f);
    glEnd();
    glPopMatrix();

	//kanan
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(-6.2,0.5,15);
    glColor3f(0.2,1.0,0.2);
    glBegin(GL_QUADS);
    glVertex3f(3.2f,0.0f,0.0f);
    glVertex3f(6.2f,0.0f,0.0f);
    glVertex3f(6.2f,1.5f,0.0f);
    glVertex3f(3.2f,1.5f,0.0f);
    glEnd();
    glPopMatrix();
    
	//kiri
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslatef(-6.2,0.5,9);
    glColor3f(0.2,1.0,0.2);
    glBegin(GL_QUADS);
    glVertex3f(3.2f,0.0f,0.0f);
    glVertex3f(6.2f,0.0f,0.0f);
    glVertex3f(6.2f,3.0f,0.0f);
    glVertex3f(3.2f,3.0f,0.0f);
    glEnd();
    glPopMatrix();
    
    
    //---------RODA 3 depan--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(10.2,0,-0.5);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9.2,0,3.1);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9.2,0,2.5);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    //---------RODA 3 belakang--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(10.2,0,-3.05);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9.2,0,0.55);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(9.2,0,-0.05);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    //---------RODA 4 depan--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(13.7,0,-0.5);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(12.7,0,3.1);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(12.7,0,2.5);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    //---------RODA 4 belakang--------------
    glPushMatrix();
    for(j=0; j<=360; j++)
    {
        glPushMatrix();
        glTranslatef(13.5,0,-3.05);
        glRotated(90,1,0,0);
        glRotated(j,0,1,0);
        glTranslatef(0,3,0.8);
        glColor3f(0.3,0.3,0.3);
        glBegin(GL_QUADS);
        glVertex3f(0,0,0);
        glVertex3f(0.1,0,0);
        glVertex3f(0.1,0.6,0);
        glVertex3f(0,0.6,0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    glPushMatrix();
    glTranslatef(12.5,0,0.55);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(12.5,0,-0.05);
    glRotated(180,1,0,0);
    glColor3f(0.3,0.3,0.3);
    glBegin(GL_TRIANGLE_FAN);
    radius=80;
    jumlah_titik=20;
    x_tengah=100;
    y_tengah=0;
    for (i=0; i<=360; i++)
    {
        float sudut=i*(2*PI/jumlah_titik);
        float x=x_tengah+radius*cos(sudut);
        float y=y_tengah+radius*sin(sudut);
        glVertex2f(x/100,y/100);
    }
    glEnd();
    glPopMatrix();
    
    glPopMatrix();
}
    
void display()
{
// Kalau move dan angle tidak nol, gerakkan kamera...
    if (deltaMove)
        moveMeFlat(deltaMove);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotated(rotAngle, 0, 1, 0); // rotate by rotAngle about y-axis
    glRotated(rotAngle1, 1, 0, 0); // rotate by rotAngle about yaxis
// Gambar grid
    Grid();
// Gambar objek
    Truk();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void pressKey(int key, int x, int y)
{
// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak
    switch (key)
    {
    case GLUT_KEY_UP :
        deltaMove = 1;
        break;
    case GLUT_KEY_DOWN :
        deltaMove = -1;
        break;
    }
}
void releaseKey(int key, int x, int y)
{
// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
// Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti
    switch (key)
    {
    case GLUT_KEY_UP :
        if (deltaMove > 0)
            deltaMove = 0;
        break;
    case GLUT_KEY_DOWN :
        if (deltaMove < 0)
            deltaMove = 0;
        break;
    }
}
// Variable untuk pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting()
{
// Fungsi mengaktifkan pencahayaan
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void)
{
    glEnable (GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,700);
    glutCreateWindow("Truk Gandeng");
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(display); // Fungsi display-nya dipanggil terusmenerus
    glutReshapeFunc(Reshape);
    lighting();
    init();
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glutMainLoop();
    return(0);
}
