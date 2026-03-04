#include <Arduino.h>
#include <pindef.h>
#include <main.h>
#include <functionality/espressoProfile.h>
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
 /*
  set temperature for thermoblock
 */
}

StatusCode handleSteps (Step steps[]) {
    StatusCode code = StatusCode::fail;
    int numSteps = sizeof(steps);
    // time
    int ellapsedTime = 0;
    int requestedTime = 0;
    // flow
    float requestedMilliliters = 0;
    // profiler response
    CurveResponse response;

    for (int i=0; i == numSteps; i++) {

      Step step = steps[i];
      requestedTime = requestedTime + step.time;
      //response = setCurve(step.requestedPressure, step.time, step.);
      // reset flow counter

      // set flow; temp; pressure for Y time
      /*
      requestedTemp(target, time, curve)
      requestedFlow(target, time, curve)
      requestedPressure(target, time, curve)
      */
    }
    return code;
}

void loop() {
  StatusCode statusCode = StatusCode::standby;
  int operationMode;
  boolean steamEnabled = false;
  int inputs=((digitalRead(SINGLE_EXTRACTION)<<OperationMode::singleExtraction) 
  |  (digitalRead(DOUBLE_EXTRACTION)<<OperationMode::doubleExtraction) 
  | (digitalRead(FLUSH)<<OperationMode::flush) 
  | digitalRead(OUTPUT_STEAM<<OperationMode::outputSteam));

  const Step preInfusion = {
      5, 
      1, 
      85, 
      3.0, 
      TimingCurves::LINEAR, 
      TimingCurves::INSTANT, 
      TimingCurves::EASE_IN, 
      {{ Trigger::MEASUREMENT, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
  };

  const Step extraction = {
      1, 
      30, 
      90, 
      9.0, 
      TimingCurves::LINEAR, 
      TimingCurves::INSTANT, 
      TimingCurves::EASE_IN, 
      {{ Trigger::MEASUREMENT, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
  };

  const Step doubleExtraction = {
      1, 
      60, 
      90, 
      9.0, 
      TimingCurves::LINEAR, 
      TimingCurves::INSTANT, 
      TimingCurves::EASE_IN, 
      {{ Trigger::MEASUREMENT, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
  };

  const Step rampDown = {
      10, 
      0, 
      STANDBY_TEMPERATURE, 
      0, 
      TimingCurves::INSTANT, 
      TimingCurves::INSTANT, 
      TimingCurves::INSTANT, 
      {{ Trigger::MEASUREMENT, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
  };

  const Step outputSteam = {
      10, 
      0, 
      OUTPUT_STEAM_PRESSURE, 
      9.0, 
      TimingCurves::INSTANT, 
      TimingCurves::INSTANT, 
      TimingCurves::INSTANT, 
      {{ Trigger::MEASUREMENT, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
  };

  Step singleExtractionSteps[3] = {preInfusion, extraction, rampDown};
  Step doubleExtractionSteps[3] = {preInfusion, extraction, rampDown};
  Step flushSteps[1] = {preInfusion};
  Step flushSteps[1] = {preInfusion};
  StatusCode statusCode; 

  switch (inputs) {
    case OperationMode::singleExtraction: {
      statusCode = handleSteps(singleExtractionSteps);
      break;
    }
    /*
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
      */
     
     default: {break;}
   }

  // intercept one extraction
  // two extractions
  // flush
  // steam
  debug(ENABLE_DEBUG);
  errorHandling(statusCode);
}
