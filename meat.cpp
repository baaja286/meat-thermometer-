#include <ESP8266WiFi.h>
#include <max6675.h>
#include <BlynkSimpleEsp8266.h>
#include "meat.h"

#define SCK 14 // d5
#define MISO 12 // d6
#define CS 16 // d0

MAX6675 thermocouple(SCK, CS, MISO);



BlynkTimer timer;

int pinData =21;  //define v21 as virtual pin that sets the alarm temp 


float cToF(float c) {
  return (c * 9 / 5) + 32.0;
}



BLYNK_WRITE(21) //takes slider value from blynk app on virtual pin 21 and sends it out to be used as set temp 
{
  pinData = param.asInt(); 
}



void meatfunction()

{ 
  float meat = thermocouple.readFahrenheit();
  Blynk.virtualWrite(7, meat);
  Blynk.virtualWrite(8, meat);



if (meat > pinData) {
  Blynk.notify("meat at temp!");

}

}

