#include <Arduino.h>
#include <pindef.h>
#include <FlowSensor.h>
// FLOW SENSOR
// Nozzle size    Pulses/litre   g/pulse   min.flowrate   max.flowrate
// 1.20mm          1925           0.5194   0.0750 l/min        0.5692 l/min
// 1,925 pulses per ml / 0,512 ML per pulse

const uint16_t pulsesPerLiter = 1925;

FlowSensor Sensor(
    pulsesPerLiter,
    FLOW_SENSOR
);

void count () {
    Sensor.count();
}

void startFlowSensor() {
    Sensor.begin(count);
}

float getML () {
    Sensor.read();
    Serial.print("\ntest");
    Serial.print((float) Sensor.getFlowRate_s());
    Serial.print("\ntest");
    return Sensor.getFlowRate_s()*1000;
}