#include <Arduino.h>
#include <Giroscopio.h>
#include <motores.h>
#include <sensorColor.h>
#include <sensorUltra.h>
#include <Servo.h>



//pista A
int pistaA[3][4]={{0,0,0,0},
                  {0,0,0,0},
                  {0,0,0,0}};
int i=0;
int j=0;
int ipos=0;
int jpos=0;
int casilla=28;
int colorCruz=0;
int lecturaMatriz=0;
int check=0;
int icruz=1000;
int jcruz=1000;
int cruzDetectada=0;
int veces=0;
int objeto=0;

long d_casilla;
String vista="izquierda";
String vistapos="izquierda";
String movimiento;

//angulo
int angulo;
int vueltaIzq=-70;
int vueltaDer=62;
int mediaVuelta=-145;




int velMotores=100;
int velVuelta=255;

//variables de ultrasonicos
long distanciaFrente,distanciaDer,distanciaIzq;
long espacio=20;


//sensor color
int colorSuelo;
int checkpoint;

//delays
int espera=1500;
int avance=650;
int delAcomodo=1250;
int adelantito=200;
int vuelta= 400;

//declaramos los objetos45,47
motores motor(5,45,47,4,49,51);
sensorUltra ultraFrente(10,11);  
sensorUltra ultraIzq(53,52);
sensorUltra ultraDer(7,6);
sensorColor sensorC(7,6,5,4,9);
Giroscopio giros(1);

Servo servito;


void setup() {
  //configuracion de motores
  motor.setup();
  motor.setSpeed(velMotores);
  motor.setSpeedVuelta(velVuelta);
  motor.setSpeed180(155);

  // //configuracion ultrasonicos
  ultraFrente.setup();
  ultraDer.setup();
  ultraIzq.setup();

  sensorC.pantallaSetup();//config pantalla lcd
  sensorC.setup();
  sensorC.iteracion(1);

  giros.setup();//config del giroscopio
  //servo
  servito.attach(A0);
  servito.write(180);


  Serial.begin(115200);

}






void loop() {
  //giro izq
  // while (true)
  // {
  //   angulo=giros.angulo();
  //   motor.girarIzq();
  //   while (angulo>vueltaIzq)
  //   {
  //     angulo=giros.angulo();
  //   }
  //   motor.stop();
  //   giros.init();
  // }
  // //giroder
  // while (true)
  // {
  //   angulo=giros.angulo();
  //   motor.girarIzq();
  //   while (angulo>vueltaIzq)
  //   {
  //     angulo=giros.angulo();
  //   }
  //   motor.stop();
  //   giros.init();
  //   delay(1000);
  // }

  // //giro 45
  // while (true)
  // {
  //  angulo=giros.angulo();
  //   motor.girarDer();
  //   while (angulo<24)
  //   {
  //   angulo=giros.angulo();
  //   }
  //   motor.stop();
  //   giros.init();
  //   delay(espera);
  // }

  // //giro135
  // while (true)
  // {
  //  angulo=giros.angulo();
  // motor.girarIzq();
  // while (angulo>-84)
  // {
  // angulo=giros.angulo();
  // }
  // motor.stop();
  // giros.init();
  // delay(espera); 
  // }

  // // carreritas
  // while (true)
  // {
  //   motor.setSpeed(255);
  //   motor.avanzar();
  //   distanciaFrente=ultraFrente.distance();
  //   while (distanciaFrente>8)
  //   {
  //     distanciaFrente=ultraFrente.distance();
  //   }
  //   motor.stop();
  //   distanciaIzq=ultraIzq.distance();
  //   if (distanciaIzq>espacio)
  //   {
  //     angulo=giros.angulo();
  //       motor.girarIzq();
  //       while (angulo>vueltaIzq)
  //       {
  //         angulo=giros.angulo();
  //       }
  //       motor.stop();
  //       giros.init();
      
  //   }
  //   else{
  //     angulo=giros.angulo();
  //       motor.girarDer();
  //       while (angulo<vueltaDer)
  //       {
  //         angulo=giros.angulo();
  //       }
  //       motor.stop();
  //       giros.init();
  //   }  
  // }
  
  
//Calibracion
  // while (true)
  // {
  //   colorSuelo=sensorC.color();
  //   sensorC.colorPrint(colorSuelo);
  // }
  
  
  
  //aqui es el codigo
 delay(1000);
 colorSuelo=sensorC.color();
  while (true){
    if (colorSuelo==20){
      colorSuelo=sensorC.color();
      sensorC.colorPrint(colorSuelo);
    }
    else if (colorSuelo==1){
        checkpoint=1;
        sensorC.colorPrint(colorSuelo);
        motor.avanzar();
        delay(avance);
        motor.stop();
        delay(espera);
        break;
    }
    // aqui van mas condiciones de los posibles chekcpoints 
    else if (colorSuelo==2||colorSuelo==3||colorSuelo==4)
    {
      checkpoint=2;
      sensorC.colorPrint(colorSuelo);
      motor.avanzar();
      delay(avance);
      motor.stop();
      delay(espera);
      break;
    }
    else if (colorSuelo==6)
    {
      checkpoint=3;
      sensorC.colorPrint(colorSuelo);
      motor.avanzar();
      delay(avance);
      motor.stop();
      delay(espera);
      break;
    }
    else if (colorSuelo==7)
    {
      checkpoint=4;
      sensorC.colorPrint(colorSuelo);
      break;
    }
  } 

  delay(espera);
  while (checkpoint==1){ 
    //DESPUES DEL CHECKPOINT
    veces=0;
    colorSuelo=sensorC.color();
    distanciaFrente=ultraFrente.distance();
    while (colorSuelo==20||colorSuelo==5||colorSuelo==6||colorSuelo==7||colorSuelo==8||colorSuelo==9||colorSuelo==1||distanciaFrente<=2)
    { 
      if (veces<3)
      {
        sensorC.colorPrint(colorSuelo);
        motor.atras();
        delay(50);
        motor.stop();
        colorSuelo=sensorC.color();
        delay(500); 
        distanciaFrente=ultraFrente.distance(); 
        veces=veces+1;
      }
      else{
        sensorC.colorPrint(colorSuelo);
        motor.avanzar();
        delay(40);
        motor.stop();
        colorSuelo=sensorC.color();
        delay(500);
        distanciaFrente=ultraFrente.distance();
        veces=0;
      }
    }
    
    if (int(pistaA[j][i])==0)
    {
       pistaA[j][i]=colorSuelo;
    }

    if ((i==icruz&&j==jcruz)&&cruzDetectada==0)
    {
      sensorC.colorPrint(colorCruz);
      cruzDetectada=1;
      // 180
      giros.coordenadas(vista,"180",i,j,vista,i,j);
      vistapos=vista;
      ipos=i;
      jpos=j;
      angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>mediaVuelta)
      {
        angulo=giros.angulo();
      }
      motor.stop();
      giros.init();

      motor.atras();
      delay(delAcomodo);
      motor.stop();
      delay(espera);
      motor.avanzar();
      delay(adelantito);
      motor.stop();
      delay(espera);

      motor.avanzar();
      delay(avance);
      motor.stop();
    }
    
    else
    {
     sensorC.colorPrint(colorSuelo);
    }
    
    sensorC.printCoor(i,j);
    d_casilla=0;

    if ((int(i)==3&&int(j)==2)||check==1)
    {
      if (cruzDetectada==1)
      {
        checkpoint=2;
      }
      else
      {
        check=1;
        int coloresDetectados=0;
        int filas=3;
        int colum=4;
        if (lecturaMatriz==0)
        {
          for (int y = 0; y < filas; y++){
            for (int x = 0; x < colum; x++)
              {
              if (int(pistaA[y][x])==0)
              {
                break;
              } 
              else{
                coloresDetectados=coloresDetectados+1;
              }
            }
          } 
        }

        if (coloresDetectados==12)
        {
          if ((int(pistaA[0][0])==int(pistaA[0][2]))&&(int(pistaA[0][2])==int(pistaA[2][2]))&&(int(pistaA[2][2])==int(pistaA[2][0])))
          {
            icruz=1;
            jcruz=1;
            colorCruz=int(pistaA[0][0]);
          } 
          else{
            icruz=2;
            jcruz=1;
            colorCruz=int(pistaA[0][3]);
          }
          check=0;
          lecturaMatriz=1;
        }
      }
    }
    

    distanciaFrente=ultraFrente.distance();
    distanciaDer=ultraDer.distance();
    distanciaIzq=ultraIzq.distance();

    if ((int(i)==3&&int(j)==2)&&cruzDetectada==0)
    {
      if (cruzDetectada==0)
      {
        giros.coordenadas(vista,"180",i,j,vista,i,j);
        vistapos=vista;
        ipos=i;
        jpos=j;
        angulo=giros.angulo();
        motor.girarIzq();
        while (angulo>mediaVuelta)
        {
          angulo=giros.angulo();
        }
        motor.stop();
        giros.init();
        delay(espera);
        motor.avanzar();
        delay(avance);
        motor.stop();
      }
      
    }
    
    else if (distanciaIzq>=espacio){

      if ((distanciaDer<=espacio&&distanciaFrente<=espacio)||(distanciaDer<=espacio&&distanciaFrente>=espacio))
      {
        String giro="izquierda";
        giros.coordenadas(vista,giro,i,j,vista,i,j);
        jpos=j;
        ipos=i;
        vistapos=vista;
        angulo=giros.angulo();
        motor.girarIzq();
        while (angulo>vueltaIzq)
        {
          angulo=giros.angulo();
        }
        motor.stop();
        giros.init();

        motor.atras();
        delay(delAcomodo);
        motor.stop();
        motor.avanzar();
        delay(adelantito);
        motor.stop();
        delay(espera);

        motor.avanzar();
        delay(avance);
        motor.stop();

      }
      else if (distanciaDer>=espacio&&distanciaFrente<=espacio)
      {
        giros.coordenadas(vista,"izquierda",i,j,vistapos,ipos,jpos);
        if (pistaA[jpos][ipos]==0)
        {
          giros.coordenadas(vista,"izquierda",i,j,vista,i,j);
          angulo=giros.angulo();
          motor.girarIzq();
          while (angulo>vueltaIzq)
          {
            angulo=giros.angulo();
          }
          motor.stop();
          giros.init();
          delay(espera);

          motor.avanzar();
          delay(avance);
          motor.stop();
        }
        else if ((ipos==icruz&&jpos==jcruz)&&cruzDetectada==0)
        {
          giros.coordenadas(vista,"izquierda",i,j,vista,i,j);
          angulo=giros.angulo();
          motor.girarIzq();
          while (angulo>vueltaIzq)
          {
            angulo=giros.angulo();
          }
          motor.stop();
          giros.init();
          delay(espera);

          motor.avanzar();
          delay(avance);
          motor.stop();
        }
        else{
          giros.coordenadas(vista,"derecha",i,j,vista,i,j);
          vistapos=vista;
          ipos=i;
          jpos=j;
          angulo=giros.angulo();
          motor.girarDer();
          while (angulo<vueltaDer)
          {
            angulo=giros.angulo();
          }
          motor.stop();
          giros.init();
          delay(espera);

          motor.avanzar();
          delay(avance);
          motor.stop();
        }
      }
    }
    else if (distanciaFrente>=espacio)
    {
      giros.coordenadas(vista,"frente",i,j,vista,i,j);
      vistapos=vista;
      ipos=i;
      jpos=j;

      motor.avanzar();
      delay(avance);
      motor.stop();
    }
    else if (distanciaDer>=espacio)
    {
        giros.coordenadas(vista,"derecha",i,j,vista,i,j);
        vistapos=vista;
        ipos=i;
        jpos=j;
        angulo=giros.angulo();
        motor.girarDer();
        while (angulo<vueltaDer)
        {
          angulo=giros.angulo();
        }
        motor.stop();
        giros.init();

        motor.atras();
        delay(delAcomodo);
        motor.stop();
        motor.avanzar();
        delay(adelantito);
        motor.stop();
        delay(500);

        motor.avanzar();
        delay(avance);
        motor.stop();
      
    }
    else 
    {
      giros.coordenadas(vista,"180",i,j,vista,i,j);
      vistapos=vista;
      ipos=i;
      jpos=j;
      angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>mediaVuelta)
      {
        angulo=giros.angulo();
      }
      motor.stop();
      giros.init();

      motor.atras();
      delay(delAcomodo);
      motor.stop();
      delay(espera);
      motor.avanzar();
      delay(adelantito);
      motor.stop();
      delay(espera);

      motor.avanzar();
      delay(avance);
      motor.stop();
    }
  }

  while (checkpoint==2){

    delay(espera);
    angulo=giros.angulo();
    motor.girarIzq();
    while (angulo>vueltaIzq)
    {
      angulo=giros.angulo();
    }
    motor.stop();
    giros.init();

    motor.atras();
    delay(delAcomodo);
    motor.stop();
    motor.avanzar();
    delay(adelantito);
    motor.stop();
    delay(espera);
    
    motor.avanzar();
    delay(avance);
    motor.stop();
    delay(1000);

    servito.write(90);
    delay(espera);


    angulo=giros.angulo();
    motor.girarDer();
    while (angulo<vueltaDer)
    {
      angulo=giros.angulo();
    }
    motor.stop();
    giros.init();

    motor.atras();
    delay(delAcomodo);
    motor.stop();
    motor.avanzar();
    delay(adelantito);
    motor.stop();
    
    distanciaFrente=ultraFrente.distance();
    motor.avanzar();
    while (distanciaFrente>30)
    {
      distanciaFrente=ultraFrente.distance();
    }
    motor.stop();
    
    int a=0;
    while (true)
    { 
      veces=0;
      if (a==0)
      {
        angulo=giros.angulo();
        motor.girarDer();
        while (angulo<24)
        {
        angulo=giros.angulo();
        }
        motor.stop();
        giros.init();
        delay(espera);

        motor.avanzar();
        delay(500);
        motor.stop();
        delay(espera);
        colorSuelo=sensorC.color();
        while (colorSuelo==20)
        { 
          if (veces<3)
          {
            sensorC.colorPrint(colorSuelo);
            motor.atras();
            delay(50);
            motor.stop();
            colorSuelo=sensorC.color();
            delay(500); 
            distanciaFrente=ultraFrente.distance(); 
            veces=veces+1;
          }
          else{
            sensorC.colorPrint(colorSuelo);
            motor.avanzar();
            delay(40);
            motor.stop();
            colorSuelo=sensorC.color();
            delay(500);
            distanciaFrente=ultraFrente.distance();
            veces=0;
          }
        }
        if (colorSuelo==4)
        {
          servito.write(180);
          delay(espera);
          motor.atras();
          delay(500);
          motor.stop();
          objeto=1;
          break;
          
        }
        else{
          delay(espera);
          motor.atras();
          delay(500);
          motor.stop();
          
        } 
        a=1; 
      }
      else if (a==1)
      {
        angulo=giros.angulo();
        motor.girarIzq();
        while (angulo>-54)
        {
        angulo=giros.angulo();
        }
        motor.stop();
        giros.init();
        delay(espera);
        motor.avanzar();
        delay(500);
        motor.stop();
        servito.write(180);
        delay(espera);
        motor.atras();
        delay(500);
        motor.stop();
        objeto=2;
        break;

      } 
    }

    if (objeto==1)
    {
     angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>-84)
      {
      angulo=giros.angulo();
      }
      motor.stop();
      giros.init();
      delay(espera); 
    }
    else if (objeto==2)
    {
      angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>-30)
      {
      angulo=giros.angulo();
      }
      motor.stop();
      giros.init();
      delay(espera);
    }

    colorSuelo=sensorC.color();
    while (colorSuelo!=6)
    {   delay(1000);
        motor.avanzar();
        delay(500);
        motor.stop();
        colorSuelo=sensorC.color();
    }

    checkpoint=3;
  }

  while (checkpoint==3)
  {
    int s=0;
    while (s==0)
    {
      motor.setSpeed(80);
      s=1;
    }
    distanciaFrente=ultraFrente.distance();
    distanciaDer=ultraDer.distance();
    distanciaIzq=ultraIzq.distance();
    colorSuelo=sensorC.color();
    delay(espera);
    motor.avanzar();
    while ((distanciaFrente<=5)&&(colorSuelo==2||colorSuelo==8))
    {
      distanciaFrente=ultraFrente.distance();
      colorSuelo=sensorC.color();
    }
    motor.stop();

    if (colorSuelo!=2||colorSuelo!=8)
    {
      if (colorSuelo==9||colorSuelo==5)
      {
      motor.atras();
      delay(100);
      motor.stop();
      }
      else if (colorSuelo==7)
      {
        motor.avanzar();
        delay(800);
        motor.stop();
        checkpoint=4;
        break;
      }
      
      
      
    }
    
    
    if (distanciaIzq>=espacio)
    {
      angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>vueltaIzq)
      {
        angulo=giros.angulo();
      }
      motor.stop();
      giros.init();
    }
    else if(distanciaIzq<=espacio)
    {
      angulo=giros.angulo();
        motor.girarDer();
        while (angulo<vueltaDer)
        {
          angulo=giros.angulo();
        }
        motor.stop();
        giros.init();
    }
    else{
      angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>mediaVuelta)
      {
        angulo=giros.angulo();
      }
      motor.stop();
      giros.init();

      motor.atras();
      delay(delAcomodo);
      motor.stop();
      delay(espera);
      motor.avanzar();
      delay(adelantito);
      motor.stop();
      delay(espera);
    }
    
  }
  

  while (checkpoint==4)
  {
    distanciaFrente=ultraFrente.distance();
    distanciaDer=ultraDer.distance();
    distanciaIzq=ultraIzq.distance();

    if (distanciaIzq>=15&& distanciaFrente<=10)
    {
      angulo=giros.angulo();
      motor.girarIzq();
      while (angulo>vueltaIzq)
      {
        angulo=giros.angulo();
      }
      motor.stop();
      giros.init();

      motor.atras();
      delay(delAcomodo);
      motor.stop();
      motor.avanzar();
      delay(adelantito);
      motor.stop();
      delay(espera);

      motor.setSpeed(255);
      while (true)
      {
        motor.avanzar();
      }
    }
    else{
      motor.setSpeed(255);
      while (true)
      {
        motor.avanzar();
      }
    }
    
  }
  
}
