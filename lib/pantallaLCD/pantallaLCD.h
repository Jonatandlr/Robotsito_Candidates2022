#ifndef pantallaLCD_h
#define pantallaLCD_h

#include <Arduino.h>

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C hola(0x27,2,1,0,4,5,6,7);

class pantallaLCD{
    public:
        pantallaLCD(int a){ _predeterminado=a;};
        void setup(){
            hola.setBacklightPin(3,POSITIVE);
            hola.setBacklight(HIGH);
            hola.begin(16,2);
            hola.clear();
            hola.setCursor(2,0);
            hola.print("TronicTeam");

        };
        void print(int color){
            _color=color;
            if (_color==1)
            {
                hola.setCursor(0,2);
                hola.print("AMARILLO");
            }
            else if (_color==2)
            {
                hola.setCursor(0,2);
                hola.print("VERDE");
            }
            else if (_color==3)
            {
                hola.setCursor(0,2);
                hola.print("AZUL");
            }
            else if (_color==4)
            {
                hola.setCursor(0,2);
                hola.print("ROJO");
            }
            else if (_color==5)
            {
                hola.setCursor(0,2);
                hola.print("BLANCO");
            }
            else if (_color==6)
            {
                hola.setCursor(0,2);
                hola.print("MORADO");
            }
            else if (_color==7)
            {
                hola.setCursor(0,2);
                hola.print("ROSA");
            }
            else if (_color==8)
            {
                hola.setCursor(0,2);
                hola.print("VERDE");
            }
            else if (_color==9)
            {
                hola.setCursor(0,2);
                hola.print("LINEA");
            }
            else if (_color==20)
            {
                hola.setCursor(0,2);
                hola.print("No Detectado");
            }
            
        };
        void clear(){
            hola.clear();
            hola.setCursor(2,0);
            hola.print("TronicTeam");
        };
        void printcordenadas(int i,int j){
            hola.setCursor(0,2);
            hola.print("i:"+String(i)+" j="+String(j));

        };
        void printdistancia(int a){
            hola.setCursor(0,2);
            hola.print(a);

        };

    private:
    int _predeterminado;
    int _color;
};



#endif