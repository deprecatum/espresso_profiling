#include <Arduino.h>
#include <pindef.h>
#include <hardware/input/sensors.h>

FlowSensor Sensorr(
    (uint16_t) 1925,
    PD2
);

void setup() {
  Serial.print("\nsetup start\n");
  Serial.begin(9600);
  startFlowSensor();
  calibratePSI();
  Serial.print("\nsetup end\n");
}

void loop() {
  Serial.print("\nloop start\n");
  Serial.print("\nFlow: ");
  Serial.print(getFlow());
  Serial.print("\nTemp: ");
  Serial.print(getTemperature());
  Serial.print("\nPressure:");
  Serial.print(getPressure());
  Serial.print("\nloop end\n");
}
