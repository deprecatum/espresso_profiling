#include <Arduino.h>
#include <pindef.h>
#include <NTC_Thermistor.h>
/*
    Dedica code 5217100200
    NTC L400 style thermistor - 100k at 25c
    B-value of 3950K-4036K
    values for B 3800
    40k at 45c
    100k at 25c
    250k at 5c
*/

#define THERMISTOR_RESISTANCE_AT_25 350000L
#define REFERENCE_RESISTANCE   THERMISTOR_RESISTANCE_AT_25
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3900
#define STM32_ANALOG_RESOLUTION 4095

NTC_Thermistor Temp_sensor(
    TEMPERATURE_SENSOR,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE,
    STM32_ANALOG_RESOLUTION
);

float getCelsius () {
    return Temp_sensor.readCelsius();
}