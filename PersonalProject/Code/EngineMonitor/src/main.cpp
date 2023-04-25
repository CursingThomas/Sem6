#include <Arduino.h>
#include <Temperature/ITemperature.h>

ITemperature x;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  x.getTemperature();
  Serial.println(12);
  delay(100);
}