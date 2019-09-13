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

// get meat temp and write it to virtual pin

void meatfunction()

{ 
  float meat = thermocouple.readFahrenheit();
  Blynk.virtualWrite(7, meat);
  Blynk.virtualWrite(8, meat);

// notify if meat temp is higher than what is set on virtual pin 21

if (meat > pinData) {
  Blynk.notify("meat at temp!");

}

}




void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Blynk.begin(AUTH, SSID, PASS);

  Serial.write("Connected to Blynk");
  // wait for MAX chip to stabilize
  delay(500);
  
  timer.setInterval(1000L, meatfunction);
}



void loop() {
  Blynk.run();
  timer.run();
}





