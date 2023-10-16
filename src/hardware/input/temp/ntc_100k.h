#include <Arduino.h>
#include <pindef.h>
#include <NTC_Thermistor.h>

// part model NTCLE400E3104H(A)
// celsius, resistance (KOHM)
// 70  15,50
// 80  10,84
// 90  7,707
// 100  5,571
// 110  4,092
// 120  3,046
// 130  2,298
// 140  1,755
// 150  1,356

#define REFERENCE_RESISTANCE   5600
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                4190
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

/* debug temp and adc resolution
float getTemp () {
  Serial.print("analogRead: ");
  Serial.print(analogRead(TEMPERATURE_SENSOR));
  Serial.print("\n");
    float Vout = analogRead(TEMPERATURE_SENSOR)* (3.3/4095); //4095 �' 12 bit resolution of the blue pill
  Serial.print("vout: ");
  Serial.print(Vout);
  Serial.print("\n");
  float R_NTC = (Vout * REFERENCE_RESISTANCE) /(3.3 - Vout); //calculating the resistance of the thermistor
  Serial.print("R_NTC: ");
  Serial.print(R_NTC);
  Serial.print("\n");
  float Temp_C = (B_VALUE/log(R_NTC/REFERENCE_RESISTANCE+B_VALUE)); //converting into Celsius
  return Temp_C;
}
 */