#include <Arduino.h>
#include <sensorColor.h>
#include <pantallaLCD.h>

pantallaLCD pantallita(1);

sensorColor::sensorColor(int s0,int s1,int s2,int s3,int out){
    _s0=s0;
    _s1=s1;
    _s2=s2;
    _s3=s3;
    _out=out;
};
void sensorColor::setup(){
    pinMode(_s0,OUTPUT);
    pinMode(_s1,OUTPUT);
    pinMode(_s2,OUTPUT);
    pinMode(_s3,OUTPUT);
    pinMode(_out,INPUT);
    
    digitalWrite(_s0,HIGH);
    digitalWrite(_s1,HIGH);
};

int sensorColor::getRed(){
    digitalWrite(_s2,LOW);
    digitalWrite(_s3,LOW);
    delay(4);
    int rojo=pulseIn(_out,HIGH);
    
    return (rojo);
};

int sensorColor::getGreen(){
    //filtro verde
    digitalWrite(_s2,HIGH);
    digitalWrite(_s3,HIGH );
    delay(4);
    int verde=pulseIn(_out,LOW);
    
    return (verde);
};

int sensorColor::getBlue(){
    //FILTRO AZUL
    digitalWrite(_s2,LOW);
    digitalWrite(_s3,HIGH );
    delay(4);
    int azul=pulseIn(_out,LOW);
    return(azul);
};

void sensorColor::print(){
    int sumaRojo=0;int sumaVerde=0;int sumaAzul=0;
    int promRojo=0;int promVerde=0;int promAzul=0;
    int intentos=0;
    
    for (size_t i = 0; i < 100; i++)
    {
        int rojo=sensorColor::getRed();
        int verde=sensorColor::getGreen();
        int azul=sensorColor::getBlue();
        sumaRojo=sumaRojo+rojo;
        sumaVerde=sumaVerde+verde;
        sumaAzul=sumaAzul+azul;
        intentos=intentos+1;
    }
    promRojo=sumaRojo/intentos;
    promVerde=sumaVerde/intentos;
    promAzul=sumaAzul/intentos;
    Serial.println("promedios");
    Serial.print("R: ");
    Serial.print(promRojo);
    Serial.print("\t");

    Serial.print("V: ");
    Serial.print(promVerde);
    Serial.print("\t");

    Serial.print("A: ");
    Serial.println(promAzul);
};
void sensorColor::printCoor(int i,int j){
        pantallita.clear();
        pantallita.printcordenadas(i,j);
        delay(500); 

};
void sensorColor::printdistancia(int a){
        pantallita.clear();
        pantallita.printdistancia(a);
        delay(500);
};


void sensorColor::colorPrint(int color){
   
    _color=color;
    if (_color==1){
        pantallita.clear();
        pantallita.print(1);//Amarillo
        delay(500);
    }
    
    else if (_color==2)
    {
        pantallita.clear();
        pantallita.print(2);//Verde
        delay(500);
        
    }
    else if (_color==3)
    {
        pantallita.clear();
        pantallita.print(3);//Azul
        delay(500);
    }
    else if (_color==4)
    {
        
        pantallita.clear();
        pantallita.print(4);//rojo
        delay(500);
    }
    else if (_color==5)
    {
        
        pantallita.clear();
        pantallita.print(5);//blanco
        delay(500);
    }
    else if (_color==6)
    {
        
        pantallita.clear();
        pantallita.print(6);//blanco
        delay(500);
    }
    else if (_color==7)
    {
        
        pantallita.clear();
        pantallita.print(7);//blanco
        delay(500);
    }
    else if (_color==8)
    {
        
        pantallita.clear();
        pantallita.print(8);//blanco
        delay(500);
    }
    else if (_color==9)
    {
        
        pantallita.clear();
        pantallita.print(9);//blanco
        delay(500);
    }

    else{
       
        pantallita.clear();
        pantallita.print(20);//No detecta
        delay(500);
        
    }
};

int sensorColor::color(){
    int sumaRojo=0;int sumaVerde=0;int sumaAzul=0;
    int promRojo=0;int promVerde=0;int promAzul=0;
    int intentos=0;
    
    for (int i = 0; i < _iteracion; i++)
    {
        int rojo=sensorColor::getRed();
        int verde=sensorColor::getGreen();
        int azul=sensorColor::getBlue();
        sumaRojo=sumaRojo+rojo;
        sumaVerde=sumaVerde+verde;
        sumaAzul=sumaAzul+azul;
        intentos=intentos+1;
    }
    promRojo=sumaRojo/intentos;
    promVerde=sumaVerde/intentos;
    promAzul=sumaAzul/intentos;
    // Serial.println("promedios");
    // Serial.print("R: ");
    // Serial.print(promRojo);
    // Serial.print("\t");

    // Serial.print("V: ");
    // Serial.print(promVerde);
    // Serial.print("\t");

    // Serial.print("A: ");
    // Serial.println(promAzul);
    // int promRojo=sensorColor::getRed();
    // int promVerde=sensorColor::getGreen();
    // int promAzul=sensorColor::getBlue();
   
    Serial.println("promedios");
    Serial.print("R: ");
    Serial.print(promRojo);
    Serial.print("\t");

    Serial.print("V: ");
    Serial.print(promVerde);
    Serial.print("\t");

    Serial.print("A: ");
    Serial.println(promAzul);

    
    if ((7<=promRojo)&&(promRojo<=13) && (0<=promVerde)&&(promVerde<=1)&& (0<=promAzul)&&(promAzul<=2)){
        return(1);   //amarillo
    }
    else if ((8<=promRojo)&&(promRojo<=14) && (8<=promVerde)&&(promVerde<=14)&& (8<=promAzul)&&(promAzul<=14)){
        return(2); //verde
    }
    else if ((1<=promRojo)&&(promRojo<=22) && (21<=promVerde)&&(promVerde<=21)&& (19<=promAzul)&&(promAzul<=21)){
        return(3);//azul
    }
    else if ((0<=promRojo)&&(promRojo<=1) && (20<=promVerde)&&(promVerde<=22)&& (20<=promAzul)&&(promAzul<=22)){
        return(4); //rojo
    }
    else if ((4<=promRojo)&&(promRojo<=6) && (0<=promVerde)&&(promVerde<=4)&& (0<=promAzul)&&(promAzul<=6)){
        return(7); //rosa
    }
    else if ((4<=promRojo)&&(promRojo<=5) && (0<=promVerde)&&(promVerde<=5)&& (4<=promAzul)&&(promAzul<=5)){
        return(5); //blanco
    }
    else if ((20<=promRojo)&&(promRojo<=26) && (20<=promVerde)&&(promVerde<=26)&& (20<=promAzul)&&(promAzul<=26)){
        return(6); //morado
    }
    else if ((27<=promRojo)&&(promRojo<=37) && (200<=promVerde)&&(promVerde<=220)&& (27<=promAzul)&&(promAzul<=100)){
        return(8); //verdeZona3
    }
    else if ((0<=promRojo)&&(promRojo<=8) && (80<=promVerde)&&(promVerde<=90)&& (2<=promAzul)&&(promAzul<=40)){
        return(9); //lineablanca
    }
    else{
       return(20);
    }
};


//funciones de la pantalla

void sensorColor::pantallaSetup(){
    pantallita.setup();
};






