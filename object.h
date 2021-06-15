#ifndef OBJECT_H
#define OBJECT_H

class Objek{
private:
    float bx;
    float by;
    float bz;
    float bsize;
    int bhitval;

public:
    //setter
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setSize(float s);
    void setHitValue(int v);

    //getter
    float getX();
    float getY();
    float getZ();
    float getSize();
    int getHitValue(); //0 berarti tidak tembus
};

class Gedung: public Objek //Gedung extends Objek
{
public:
    Gedung(float x, float y, float z, float s, float cr, float cg, float cb); //constructor
};


#endif // OBJECT_H
