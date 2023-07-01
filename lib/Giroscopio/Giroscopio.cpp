#include <Arduino.h>

#include <Wire.h>

#include <Giroscopio.h>



void Giroscopio::setup(){
    Wire.begin(); // D2(GPIO4)=SDA / D1(GPIO5)=SCL
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);


};
void Giroscopio::init(){
    ang=0;
    Angle[2]=0;
};


int Giroscopio::angulo(){

   Wire.beginTransmission(MPU);
   Wire.write(0x3B); //Pedir el registro 0x3B - corresponde al AcX
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x3B, se piden 6 registros
   AcX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   AcY=Wire.read()<<8|Wire.read();
   AcZ=Wire.read()<<8|Wire.read();
 
   //A partir de los valores del acelerometro, se calculan los angulos Y, X
   //respectivamente, con la formula de la tangente.
   Acc[1] = atan(-1*(AcX/A_R)/sqrt(pow((AcY/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
   Acc[0] = atan((AcY/A_R)/sqrt(pow((AcX/A_R),2) + pow((AcZ/A_R),2)))*RAD_TO_DEG;
 
   //Leer los valores del Giroscopio
   Wire.beginTransmission(MPU);
   Wire.write(0x43);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU,6,true);   //A partir del 0x43, se piden 6 registros
   GyX=Wire.read()<<8|Wire.read(); //Cada valor ocupa 2 registros
   GyY=Wire.read()<<8|Wire.read();
   GyZ=Wire.read()<<8|Wire.read();
 
   //Calculo del angulo del Giroscopio
   Gy[0] = GyX/G_R;
   Gy[1] = GyY/G_R;
   Gy[2] = GyZ/G_R;

   dt = (millis() - tiempo_prev) / 1000.0;
   tiempo_prev = millis();
 
   //Aplicar el Filtro Complementario
   Angle[0] = 0.98 *(Angle[0]+Gy[0]*dt) + 0.02*Acc[0];
   Angle[1] = 0.98 *(Angle[1]+Gy[1]*dt) + 0.02*Acc[1];

   //Integración respecto del tiempo paras calcular el YAW
   Angle[2] = Angle[2]+Gy[2]*dt;
 
   //Mostrar los valores por consola
   ang=Angle[2];
    
   return(ang);
   delay(10);
};


void Giroscopio::coordenadas(String vista,String giro,int i, int j,String& vistaNew,int& iNew,int& jNew){
    //vuellta izquierda
    if (vista=="izquierda"&& giro=="izquierda")
    {
        vistaNew="abajo";
        jNew=j+1;
    }
    else if (vista=="abajo"&& giro=="izquierda")
    {
        vistaNew="derecha";
        iNew=i-1;
    }
    else if (vista=="derecha"&& giro=="izquierda")
    {
        vistaNew="arriba";
        jNew=j-1;
    }
    else if (vista=="arriba"&& giro=="izquierda")
    {
        vistaNew="izquierda";
        iNew=i+1;
    }
    //vuelta derecha
    else if (vista=="izquierda"&& giro=="derecha")
    {
        vistaNew="arriba";
        jNew=j-1;
    }
    else if (vista=="arriba"&& giro=="derecha")
    {
        vistaNew="derecha";
        iNew=i-1;
    }
    else if (vista=="derecha"&& giro=="derecha")
    {
        vistaNew="abajo";
        jNew=j+1;
    }
    else if (vista=="abajo"&& giro=="derecha")
    {
        vistaNew="izquierda";
        iNew=i+1;
    }
    //enfrente
    else if (vista=="abajo"&& giro=="frente")
    {
        vistaNew="abajo";
        jNew=j+1;
    }
    else if (vista=="izquierda"&& giro=="frente")
    {
        vistaNew="izquierda";
        iNew=i+1;
    }
    else if (vista=="arriba"&& giro=="frente")
    {
        vistaNew="arriba";
        jNew=j-1;
    }
    else if (vista=="derecha"&& giro=="frente")
    {
        vistaNew="derecha";
        iNew=i-1;
    }
    //giro 180
    else if (vista=="derecha"&& giro=="180")
    {
        vistaNew="izquierda";
        iNew=i+1;
    }
    else if (vista=="izquierda"&& giro=="180")
    {
        vistaNew="derecha";
        iNew=i-1;
    }
    else if (vista=="arriba"&& giro=="180")
    {
        vistaNew="abajo";
        jNew=j+1;
    }
    else if (vista=="abajo"&& giro=="180")
    {
        vistaNew="arriba";
        jNew=j-1;
    }

};

