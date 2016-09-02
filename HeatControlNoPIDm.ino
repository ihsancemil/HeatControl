#include "ControlF.h"
#include <OneWire.h>
#include <DallasTemperature.h>

//define inputs
#define TARGETHEATPIN A0

//define outputs
#define HEATER 9
#define COOLER 6

//define constant variable
#define maxHeat 100
#define minHeat 60

//define temp sensors
#define CURRENTHEATPIN 2
OneWire oneWire(CURRENTHEATPIN);
DallasTemperature sensors(&oneWire);

void setup() {
  //set input pins
  pinMode(TARGETHEATPIN, INPUT);
  
  //set output pins
  pinMode(HEATER, OUTPUT); 
  pinMode(COOLER, OUTPUT);

  
  Serial.begin(9600); // To Show the current heat
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();
  float currentHeat = sensors.getTempCByIndex(0);
  float targetHeat = map(analogRead(TARGETHEATPIN), 0, 1023, 60, 100);
  targetHeat = targetHeat/2;
  float power = PCalculate(currentHeat, targetHeat, (maxHeat-minHeat)/2); //PowerCalculator
  //Serial.print("Heat:"); 
  Serial.print(currentHeat);
  Serial.print(",");
  //Serial.print("Pot:"); 
  Serial.println(targetHeat);
  
  if(power<0){
    power = map(power, -100, 0, 0, 255); //set Values between 0-255
    analogWrite(HEATER, 255);
    analogWrite(COOLER, power);
  }
  else if(power>=0){
    power = map(power, 0, 100, 255, 0); //set Values between 0-255
    analogWrite(HEATER, power);
    analogWrite(COOLER, 255);
  }
}
