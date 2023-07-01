#ifndef Giroscopio_h
#define Giroscopio_h

//Direccion I2C de la IMU
#define MPU 0x68
 
//Ratios de conversion
#define A_R 16384.0 // 32768/2
#define G_R 131.0 // 32768/250
 
//Conversion de radianes a grados 180/PI
#define RAD_A_DEG = 57.295779

#include <Arduino.h>


class Giroscopio{

    public:

        Giroscopio(int predeterminado){_predeterminado=predeterminado;};
        void setup();
        void init();
        int angulo();
        void coordenadas(String vista,String giro,int i, int j,String& vistaNew,int& iNew,int& jNew);
        
        
        
        

    private:


    int _predeterminado; //variable para establecer el constructor 

    
    //Valores RAW
    int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

    //Angulos
    float Acc[2];
    float Gy[3];
    float Angle[3];

    String valores;

    long tiempo_prev;
    float dt;
    int ang;
    int _i;
    int _j;
    int _posicion;


};



#endif 
