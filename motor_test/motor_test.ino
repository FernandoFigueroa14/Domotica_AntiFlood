#include "NXTIoT_dev.h"

NXTIoT_dev  mysigfox;

// Definicion de pines necesarios conectados a nuestro Arduino
const int boton=6;
const int sensorPinHumedad=A0;
const int sensorPinAgua = A1;
const int sensorObstaculo = 2;

const int enPin = 3; // PWM se conecta al pin 1 del puente-H
const int in1Pin = 4; // Entrada 2 del puente-H
const int in2Pin = 5; // Entrada 7 del puente-H

int obstaculo = 0;
int humedad = 0;
int sensorAgua = 0;
int posicion = 0;

int period = 30000;
unsigned long time_now = 0;
 
void setup() {
  Serial.begin(9600); //Iniciamos la comunicacion serial
  pinMode(in1Pin, OUTPUT); 
  pinMode(in2Pin, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(sensorObstaculo,INPUT); 
  analogWrite(enPin, 80);
}

void motor(int ch, int t){
    if (ch == 1) {
      Serial.println("Girando en sentido horario...");
      digitalWrite(in1Pin,LOW);
      digitalWrite(in2Pin,HIGH);
      delay(t);
      digitalWrite(in2Pin,LOW);
    }
    else if (ch == 0) { 
      Serial.println("Girando en sentido anti-horario...");
      digitalWrite(in1Pin,HIGH);
      digitalWrite(in2Pin,LOW);
      delay(t);
      digitalWrite(in1Pin,LOW);
    }
}

void sensores()
{
  //Sensor Humedad
  humedad=analogRead(sensorPinHumedad);
  /*
  Serial.print("Lectura SensorHumedad:");
  Serial.println(humedad);
   if(humedad >= 0 & humedad <= 300){
        Serial.println("Sensor en agua");  
    } else if(humedad > 301 & humedad <= 700){
        Serial.println("Sensor en suelo húmedo");
    }else if(humedad >= 701){
       Serial.println("Sensor en suelo");
    }*/

    //Sensor agua
    
    sensorAgua= analogRead(sensorPinAgua);
    /*Serial.print("Lectura SensorAgua: ");
    Serial.println(sensorAgua*100/1024);
    Serial.print("%");
    if(sensorAgua == 0){
      Serial.println("Sensor seco");
    }
    else if (sensorAgua > 0){
      Serial.println("Sensor mojado");
    }*/

    //Sensor Obstaculo
    obstaculo = digitalRead(sensorObstaculo);
/*
    if (value == HIGH){
         Serial.println ("NO DETECTO NADA");
         mysigfox.initpayload();
         mysigfox.addint(0);
         mysigfox.sendmessage();
    }
    else{
        Serial.println("DETECTE ALGO");
        mysigfox.initpayload();
        mysigfox.addint(1);
        mysigfox.sendmessage();
        
    }

    

  mysigfox.initpayload();
  mysigfox.addint(humedad);
  mysigfox.addint(sensorAgua);
  mysigfox.sendmessage();*/
  
}

void sigfoxSend(){
  mysigfox.initpayload();
  if(humedad >= 0 & humedad <= 600){
     mysigfox.addint(2);  
  } else if(humedad > 601 & humedad <= 1000){
     mysigfox.addint(1);
  }else if(humedad >= 1001){
     mysigfox.addint(0);
  }

  if(sensorAgua == 0){
      mysigfox.addint(0);
  }else if (sensorAgua > 0){
      mysigfox.addint(1);
  }

  if(posicion == 2){
     mysigfox.addint(2);  
  } else if(posicion == 1){
     mysigfox.addint(1);
  }else if(posicion == 0){
     mysigfox.addint(0);
  }

  mysigfox.sendmessage();
  
}

void loop() { 
    sensores();
    if((humedad >= 0 & humedad <= 600) & obstaculo == HIGH){
        Serial.println("Subiendo barrera");
        motor(1, 4000);
        posicion = 2;
    } else if((humedad > 601 & humedad <= 1000) & obstaculo == HIGH){
        Serial.println("Subiendo a la mitad la barrera");
        motor(1, 2000);
        posicion = 1;
    }else if((humedad >= 1001) & obstaculo == LOW){
       Serial.println("Bajando barrera");
        motor(0, 4000);
        posicion = 0;
    }

    if(millis() > time_now + period){
        time_now = millis();
        sigfoxSend();
    }
}
