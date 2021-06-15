#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "object.h"

double rotAngle = 20; // rotation angle (BEWARE: Global)
double rotAngle1 = 20; // rotation angle (BEWARE: Global)
float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=20.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
float xStreet = 0, yStreet = 0, zStreet = 0;
int deltaMove = 0,h,w;
int bitmapHeight=12;
const double PI = 3.141592653589793;
int i,j,radius,jumlah_titik,x_tengah,y_tengah;
const float Z_MIN_JALAN = -1200, Z_MAX_JALAN = 200;
const float X_MIN_JALAN = -20, X_MAX_JALAN = 20;
int buildings = 1;
int isNaik = 0;
double y_gerbang = 0.15;

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

void moveMeFlat(double i)
{
// Fungsi ini untuk maju mundur kamera
    x = x + (i/4)*(lx)*1;
    y = y + (i/4)*(ly)*1;
    z = z + (i/4)*(lz)*1;
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
       case 'o': // maju
        if(zStreet  < -1*(Z_MIN_JALAN + 30)){
        	if(isNaik == 0){	
        		if(zStreet < 485 || zStreet > 496){
        			zStreet += 2;
        		}
        	}else{
        		zStreet += 2;
       	 	}
        }
        
        break;
    case 'l': // mundur
    	if(zStreet > -1*(Z_MAX_JALAN - 10)){
    			if(isNaik == 0){
    			if(zStreet > 510 || zStreet < 496){
    				zStreet -= 2;
    			}
    		}else{
    			zStreet -= 2;
    		}
    	}
        
        break;
	case 'k': // kiri
		if(xStreet*(-1) > X_MIN_JALAN+2){
	        xStreet += 1;	
		} 
        break;
    case ';': // kanan
        if(xStreet*(-1) < X_MAX_JALAN-3){
	        xStreet -= 1;	
		}
        break;
    case 'n': // buka gerbang
    	isNaik = 1;
    	break;
    case 'm': // tutup gerbang
    	isNaik = 0;
    	break;
    case 'q':
        exit(0); // exit
    }
    glutPostRedisplay();
}

void gerbangNaik(){
	if(isNaik == 1){
		if(y_gerbang < 0.4){
			y_gerbang += 0.005;
		}
	}else{
		if(y_gerbang > 0.15){
			y_gerbang -= 0.005;
		}
	}
}

void gedung(){
	if (buildings){
        //Gedung kanan
        Gedung kantor1a(40,12,-30,25,0.8,0.8,0.8);
        Gedung kantor2a(40,10,10,25,0.4,0.6,0.4);
        Gedung kantor3a(40,10,70,25,0.4,0.4,0.7);
        Gedung kantor4a(40,10,110,25,0.4,0.4,0.4);
        Gedung kantor5a(40,10,150,25,0.6,0.4,0.4);
        Gedung kantor6a(40,10,-200,25,0.8,0.8,0.4);
        Gedung kantor7a(40,10,-240,25,0.4,0.4,0.6);
        Gedung kantor8a(50,10,250,50,0.4,0.4,0.6);
        Gedung kantor9a(40,3,-50,10,0.2,0.4,0.4); //kecil1
        Gedung kantor11a(80,3,-80,10,0.7,0.4,0.4); //kecil3
        Gedung kantor12a(40,3,-95,10,0.4,0.6,0.4); //kecil4
        Gedung kantor14a(40,3,-125,10,0.5,0.4,0.5); //kecil6
        Gedung kantor15a(40,10,-160,25,0.6,0.6,0.6); //kecil7
        Gedung kantor16a(40,10,360,25,0.6,0.6,0.6);

        //gedung kiri
        Gedung kantor1b(-50,20,300,50,0.4,0.9,0.4);
        Gedung kantor3b(-30,0,380,10,0.4,0.4,0.9); //kecil2
        Gedung kantor2b(-30,5,360,10,0.9,0.4,0.4); //kecil1
        Gedung kantor4b(-30,5,340,10,0.4,0.9,0.9); //kecil3
        Gedung kantor5b(-40,10,240,25,0.9,0.4,0.9);
        Gedung kantor6b(-40,10,200,25,0.9,0.9,0.4);
        Gedung kantor7b(-40,10,160,25,0.7,0.5,0.7);
        Gedung kantor8b(-40,10,120,25,0.5,0.5,0.7);
        Gedung kantor9b(-40,10,20,25,0.5,0.7,0.7);
        Gedung kantor10b(-40,10,-20,25,0.7,0.7,0.5);
        Gedung kantor11b(-50,20,-100,50,0.6,0.9,0.7);
        Gedung kantor12b(-40,10,-140,25,0.7,0.3,0.6);
    }
}

void pohon(){
	//batang
		glPushMatrix();
			glColor3ub(122, 61, 31);
			glRotated(270, 1, 0, 0);
			glTranslatef(5, -10, 0);
			gluCylinder(gluNewQuadric(), 1.5, 0.5, 9.5, 25, 25);
		glPopMatrix();
		
		//daun
		glPushMatrix();
			glColor3ub(25, 148, 19);
			glScaled(2, 2, 2);
			glRotated(90, 0, 1, 0);
			glTranslatef(-5, 6.2, 2.5);
			glutSolidDodecahedron();
		glPopMatrix();
		glPushMatrix();
			glColor3ub(18,118,13);
			glScaled(2, 2, 2);
			glRotated(90, 0, 1, 0);
			glTranslatef(-5, 5.2, 1.5);
			glutSolidDodecahedron();
		glPopMatrix();
		glPushMatrix();
			glColor3ub(30, 130, 25);
			glScaled(2, 2, 2);
			glRotated(90, 0, 1, 0);
			glTranslatef(-5, 5.2, 3.5);
			glutSolidDodecahedron();
		glPopMatrix();
}

void gerbang(){
	glColor3f(0.0,0.0,0.0);
	glTranslatef(25,1,-500); //koordinat tiang item
	glScaled(10, 50, 3); //perbesaran tiang item
	glutSolidCube(1);
	glTranslatef(-5, 0, 0);
	glutSolidCube(1);
	
	glColor3f(0.1, 0.1, 0.3);
	glTranslatef(2.5,y_gerbang,0); //koordinat papan merah
	glScaled(5, 0.3, 1.1); //perbesaran papan merah
	glutSolidCube(1);
}

void landmark()
{
	//kiri jalan
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
    	glVertex3f(X_MIN_JALAN, -0.01, Z_MIN_JALAN);
    	glVertex3f(X_MIN_JALAN, -0.01, Z_MAX_JALAN);
    	glVertex3f(X_MIN_JALAN, 1.5 , Z_MAX_JALAN);
    	glVertex3f(X_MIN_JALAN, 1.5, Z_MIN_JALAN);
    glEnd();
    
    glColor3f(0.0, 0.8, 0.4);
    glBegin(GL_QUADS);
    	glVertex3f(-400, 1.5, Z_MIN_JALAN);
    	glVertex3f(-400, 1.5, Z_MAX_JALAN);
    	glVertex3f(X_MIN_JALAN, 1.5, Z_MAX_JALAN);
    	glVertex3f(X_MIN_JALAN, 1.5, Z_MIN_JALAN);
    glEnd();
    glPopMatrix();
	
	//jalan tengah
	glPushMatrix();
	glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_QUADS);
    	glVertex3f(X_MIN_JALAN, -0.01, Z_MIN_JALAN);
    	glVertex3f(X_MIN_JALAN, -0.01, Z_MAX_JALAN);
    	glVertex3f(X_MAX_JALAN, -0.01, Z_MAX_JALAN);
    	glVertex3f(X_MAX_JALAN, -0.01, Z_MIN_JALAN);
    glEnd();
    glPopMatrix();
    
    // garis tengah
    glPushMatrix();
    for(int i = Z_MAX_JALAN; i > Z_MIN_JALAN; i = i - 20){
    	glColor3f(1.0, 1.0, 1.0);
    	glBegin(GL_QUADS);
    		glVertex3f(-0.5, 0.2, i);
    		glVertex3f(-0.5, 0.2, i-10);
    		glVertex3f(0.5, 0.2, i-10);
    		glVertex3f(0.5, 0.2, i);
    	glEnd();
    }
    glPopMatrix();
    
    //kanan jalan
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
	glBegin(GL_QUADS);
    	glVertex3f(X_MAX_JALAN, -0.01, Z_MIN_JALAN);
    	glVertex3f(X_MAX_JALAN, -0.01, Z_MAX_JALAN);
    	glVertex3f(X_MAX_JALAN, 1.5, Z_MAX_JALAN);
    	glVertex3f(X_MAX_JALAN, 1.5, Z_MIN_JALAN);
    glEnd();
    
    glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_QUADS);
    	glVertex3f(X_MAX_JALAN, 1.5, Z_MIN_JALAN);
    	glVertex3f(X_MAX_JALAN, 1.5, Z_MAX_JALAN);
    	glVertex3f(400, 1.5, Z_MAX_JALAN);
    	glVertex3f(400, 1.5, Z_MIN_JALAN);
    glEnd();
    glPopMatrix();
    
    //gedung
    glPushMatrix();
   		glTranslated(0, 3, -200);
    	gedung();
    glPopMatrix();
    
    glPushMatrix();
    	glRotated(180, 0, 1, 0);
   		glTranslated(0, 3, 800);
    	gedung();
    glPopMatrix();
    
    //gerbang
	glPushMatrix();
		gerbang();
	glPopMatrix();
	
	//Pohon sebelum gebang
	//POHON Kiri
	//pohon kiri depan
	glPushMatrix();
		glTranslated(-35, 1.5, -452);
		glScaled(1.2, 1.2, 1.2);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-40, 1.5, -455);
		glScaled(2.0, 2.0, 2.0);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -438);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -390);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -385);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -260);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -250);
		glScaled(0.6, 0.6, 0.6);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -160);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -140);
		glScaled(1.5, 1.5, 1.5);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, -110);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(-35, 1.5, 10);
		pohon();
	glPopMatrix();
	//pohon kiri belakang
	glPushMatrix();
		glTranslated(-35, 1.5, 55);
		pohon();
	glPopMatrix();
	
	//POHON Kanan
	//pohon kanan depan
	glPushMatrix();
		glTranslated(35, 1.5, -491);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	
	glPushMatrix();
		glTranslated(35, 1.5, -490);
		glScaled(1.5, 1.5, 1.5);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -475);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -385);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -345);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -300);
		glScaled(1.5, 1.5, 1.5);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -285);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -165);
		glScaled(1.5, 1.5, 1.5);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -120);
		glScaled(0.8, 0.8, 0.8);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, -25);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, 0);
		glScaled(1.2, 1.2, 1.2);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, 90);
		pohon();
	glPopMatrix();
	
	//pohon kanan belakang
	glPushMatrix();
		glTranslated(35, 1.5, 120);
		glScaled(1.2, 1.2, 1.2);
		pohon();
	glPopMatrix();
	glPushMatrix();
		glTranslated(35, 1.5, 175);
		glScaled(1.2, 1.2, 1.2);
		pohon();
	glPopMatrix();
	
	//pohon sesudah gerbang
	glPushMatrix();
    	glRotated(180, 0, 1, 0);
   		glTranslated(0, 0, 1000);
		glPushMatrix();
			glTranslated(-35, 1.5, -452);
			glScaled(1.2, 1.2, 1.2);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-40, 1.5, -455);
			glScaled(2.0, 2.0, 2.0);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -438);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -390);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -385);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -260);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -250);
			glScaled(0.6, 0.6, 0.6);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -160);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -140);
			glScaled(1.5, 1.5, 1.5);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, -110);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, 10);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(-35, 1.5, 55);
			pohon();
		glPopMatrix();
		
		glPushMatrix();
			glTranslated(35, 1.5, -491);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -490);
			glScaled(1.5, 1.5, 1.5);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -475);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -385);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -345);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -300);
			glScaled(1.5, 1.5, 1.5);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -285);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -165);
			glScaled(1.5, 1.5, 1.5);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -120);
			glScaled(0.8, 0.8, 0.8);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, -25);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, 0);
			glScaled(1.2, 1.2, 1.2);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, 90);
			pohon();
		glPopMatrix();
	
		glPushMatrix();
			glTranslated(35, 1.5, 120);
			glScaled(1.2, 1.2, 1.2);
			pohon();
		glPopMatrix();
		glPushMatrix();
			glTranslated(35, 1.5, 175);
			glScaled(1.2, 1.2, 1.2);
			pohon();
		glPopMatrix();
    glPopMatrix();
}

void Truk()
{
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glScaled(1.1, 1.1, 1.1);
    glTranslatef(-10,0.8,-2);
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
	glPushMatrix();
    glTranslated(xStreet,0,zStreet);
    gerbangNaik();
    landmark();
    glPopMatrix();
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
    glClearColor(0.64f,0.83f,0.93f,0.0f);
    glutMainLoop();
    return(0);
}
