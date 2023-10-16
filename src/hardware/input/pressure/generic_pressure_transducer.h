#include <Arduino.h>
#include <pindef.h>
#include <reference_values.h>
// pressure sensor 500 psi
// Volts     PSI
// 0.5       0
// 1         125 psi
// 1.1745    130.5
// 2.5       250
// 3.3       366,67
// 4.5       500
//
// 1 atm = 430 mV
// 7psi = 50 mV

const float maxPSI = 500.0;
const float sensorFloor = 500.0 / MV_PER_ADC;

const float PSIperADC = maxPSI/(ADC_RESOLUTION - 1000.0 / MV_PER_ADC);

float baselinePSI = 0;

void calibratePSI () {
    Serial.print("\nsensorFloor");
    Serial.print(sensorFloor);
    Serial.print("\nPSIperADC");
    Serial.print(PSIperADC);
    Serial.print("\nPSIperADC");
    Serial.print((1000.0 / MV_PER_ADC));
    float psiSum = 0.0;
    int sampleCount = 10;
    for (int count = 1; count <= sampleCount; count++) {
        psiSum += (analogRead(PRESSURE_SENSOR) - sensorFloor) * PSIperADC;
    }
    baselinePSI -= psiSum / sampleCount;
}

float getPSI () {
    return baselinePSI + (analogRead(PRESSURE_SENSOR) - sensorFloor) * PSIperADC;
}