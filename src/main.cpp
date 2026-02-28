#include <Arduino.h>
#include <pindef.h>
#include <main.h>
#include <functionality/steam.cpp>
#include <functionality/profiling.h>
#include <functionality/extraction.cpp>

StatusCode extractOneCoffe() {
  StatusCode statusCode = StatusCode::success;
  
  return statusCode;
}

void errorHandling(StatusCode statusCode) {
  switch (statusCode) {
    case StatusCode::success: {
      Serial.print("Success !!!\n");
      delay(500);
      return;
      break;
    }
    default: {
      while (true) {
        delay(500);
        Serial.print("System failure :\n");
        Serial.print(statusCode);
        Serial.print("System failure !!!\n");
      }
      break;
    }
  }

  return;
}

void setup() {

  analogReadResolution(12);
  Serial.begin(9600);

  // define pin 
  // MACHINE SENSORS // OUTPUTS
  pinMode(PUMP_RELAY, OUTPUT);
  pinMode(THERMOBLOCK_RELAY, OUTPUT);
  pinMode(FLOW_SENSOR, OUTPUT);
  pinMode(PRESSURE_SENSOR, OUTPUT);
  pinMode(TEMPERATURE_SENSOR, OUTPUT);
  pinMode(TEMPERATURE_SENSOR_SUPPORT, OUTPUT);
  pinMode(PUMP_RELAY, OUTPUT);
  pinMode(PUMP_RELAY, OUTPUT);
  
  // USER INTERFACE BUTTONS
  pinMode(SINGLE_EXTRACTION, INPUT_PULLUP);
  pinMode(DOUBLE_EXTRACTION, INPUT_PULLUP);
  pinMode(FLUSH, INPUT_PULLUP);
  pinMode(OUTPUT_STEAM, INPUT_PULLUP);

  // convert to bit mask read, and use switch case for the options, using binary
}

void loop() {
  StatusCode statusCode = StatusCode::standby;
  Mode mode;
  boolean steamEnabled = false;
  if (digitalRead(SINGLE_EXTRACTION) == LOW) {
    
  }
  if (digitalRead(DOUBLE_EXTRACTION) == LOW) {
    
  }
  if (digitalRead(FLUSH) == LOW) {
    
  }

  steamEnabled = digitalRead(OUTPUT_STEAM) == LOW;

  if (mode && !steamEnabled) {
    statusCode = outputMode();
  } else if (
    steamEnabled
  ) {
    statusCode = outputSteam();
  }

  // intercept one extraction
  // two extractions
  // flush
  // steam
  debug(ENABLE_DEBUG);
  errorHandling(statusCode);
}

void debug (boolean enabled) {
  if (!enabled) {
    Serial.print("Flow: ");
    //Serial.print(getFlow());
    Serial.print("\nTemp: ");
    //Serial.print(getTemperature());
    Serial.print("\nPressure:");
    //Serial.print(getPressure());
    digitalWrite(16, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);                      // wait for a second
    digitalWrite(16, LOW);   // turn the LED off by making the voltage LOW
    delay(500); 
  }
}