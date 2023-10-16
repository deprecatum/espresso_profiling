#include <Arduino.h>
#include <pindef.h>
#include <hardware/input/sensors.h>

void setup() {
  analogReadResolution(12);
  Serial.begin(9600);
  pinMode(16, OUTPUT);
  Serial.print("program start\n");
}

void loop() {
  Serial.print("Flow: ");
  Serial.print(getFlow());
  Serial.print("\nTemp: ");
  Serial.print(getTemperature());
  Serial.print("\nPressure:");
  Serial.print(getPressure());
  digitalWrite(16, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                      // wait for a second
  digitalWrite(16, LOW);   // turn the LED off by making the voltage LOW
  delay(500);         
}
