#include "object.h"
#include <windows.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Objek::setX(float x){
    bx = x;
}

void Objek::setY(float y){
    by = y;
}

void Objek::setZ(float z){
    bz = z;
}

void Objek::setSize(float s){
    bsize = s;
}

void Objek::setHitValue(int v){
    bhitval = v;
}

float Objek::getX(){
    return bx;
}

float Objek::getY(){
    return by;
}

float Objek::getZ(){
    return bz;
}

float Objek::getSize(){
    return bsize;
}

Gedung::Gedung(float x, float y, float z, float s, float cr, float cg, float cb){
    setX(x);
    setY(y);
    setZ(z);
    setSize(s);
    setHitValue(0);

    glPushMatrix();
    glTranslatef(getX(),getY(), getZ());
        glPushMatrix();
            glColor3f(cr, cg, cb);
            glutSolidCube(getSize());
        glPopMatrix();
    glPopMatrix();
}

