#include <Arduino.h>
#include <sensorUltra.h>

sensorUltra::sensorUltra(int trig,int echo){
    _trig=trig;
    _echo=echo;
};

void sensorUltra::setup(){
    pinMode(_trig,OUTPUT);
    pinMode(_echo,INPUT);
    digitalWrite(_trig,LOW);
};


int sensorUltra::distance(){
    long tiempo,distancia;
    digitalWrite(_trig,HIGH);
    delay(4);
    digitalWrite(_trig,LOW);
    tiempo=pulseIn(_echo,HIGH);
    distancia=tiempo/58;
    return (distancia);
};
