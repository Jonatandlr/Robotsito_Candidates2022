#ifndef sensorColor_h
#define sensorColor_h

#include <Arduino.h>


class sensorColor{
    public:
        sensorColor(int s0,int s1,int s2,int s3,int out);
        void setup();
        int getRed();
        int getGreen();
        int getBlue();
        int color();
        void iteracion(int a){_iteracion=a;}
        void colorPrint(int color);
        void print();
        void printCoor(int i,int j);
        void printdistancia(int a);

        //funciones de la pantalla
        void pantallaSetup();

    private:
    int _s0;
    int _s1;
    int _s2;
    int _s3;
    int _out;
    int _color;
    int _iteracion;
};



#endif