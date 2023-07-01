#ifndef sensorUltra_h
#define sensorUltra_h

#include <Arduino.h>


class sensorUltra{
    public:
        sensorUltra(int trig,int echo);
        void setup();
        int distance();

    private:
        int _trig;
        int _echo;
        int _distance;
};

#endif 