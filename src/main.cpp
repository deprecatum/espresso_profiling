#include <Arduino.h>
#include <pindef.h>
#include <main.h>
#include <functionality/steam.cpp>
#include <functionality/profiling.h>
#include <functionality/extraction.cpp>

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

  /*
  convert code to use registers instead like GPIOA and GPIOB to set all pints, 
  and use switch case with bit operators to identify buttons 
  */
}

void loop() {
  StatusCode statusCode = StatusCode::standby;
  int operationMode;
  boolean steamEnabled = false;
  int inputs=((digitalRead(SINGLE_EXTRACTION)<<OperationMode::singleExtraction) 
  |  (digitalRead(DOUBLE_EXTRACTION)<<OperationMode::doubleExtraction) 
  | (digitalRead(FLUSH)<<OperationMode::flush) 
  | digitalRead(OUTPUT_STEAM<<OperationMode::outputSteam)):

  /*
  switch (inputs) {
  case OperationMode::singleExtraction: 
       statusCode = outputMode(1);
       break;
     
     case OperationMode::doubleExtraction: 
       statusCode = outputMode(1);
       break;
     
     case OperationMode::flush: 
       statusCode = outputMode(1);
       break;
     case OperationMode::outputSteam: 
       steamEnabled = true;
       statusCode = outputSteam();
       break;
     
     default: break;
   }
  */

  if (mode && !steamEnabled) {
    statusCode = outputMode();
  } else if (
    steamEnabled
  ) {
  }

  // intercept one extraction
  // two extractions
  // flush
  // steam
  debug(ENABLE_DEBUG);
  errorHandling(statusCode);
}
