#include <Arduino.h>

enum class TimingCurves {
  EASE_IN,
  EASE_OUT,
  EASE_IN_OUT,
  LINEAR,
  INSTANT,
};

struct Flag {
    Trigger trigger;
    TriggerThreshold Threshold;
};

enum class Trigger {
    TIME,
    FLOW,
    TEMP,
    PRESSURE
};

enum class TriggerThreshold {
    ABOVE,
    BELOW,
    EXACT,
};

float curve (float percentage, TimingCurves curve) {
    switch (curve) {
        case TimingCurves::EASE_IN:
            //x^2
            return pow(percentage, 2);
        case TimingCurves::EASE_OUT:
            //sqrt(x)
            return sqrt(percentage);
        case TimingCurves::EASE_IN_OUT:
            //y=(1.6x-0.8)^{3}+0.5
            return pow((1.6*percentage-0.8), 3)+0.5;
        case TimingCurves::LINEAR:
            return percentage;
        case TimingCurves::INSTANT:
            return 1;
    }
};

const struct step {
    // seconds
    int time;
    // ML/s
    float requestedFlow;
    // Celsius
    float requestedTemp;
    // PSI
    float requestedPressure;
    TimingCurves flowCurve;
    TimingCurves flowTemp;
    TimingCurves flowPressure;
    // go to next step based on flags
    Flag flags[];
};

const step preInfusion = {
    10, 
    1.1, 
    1.1, 
    1.1, 
    TimingCurves::LINEAR, 
    TimingCurves::INSTANT, 
    TimingCurves::LINEAR, 
    {{ Trigger::PRESSURE, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
};

const step rampUp = {
    1, 
    1.1, 
    1.1, 
    1.1, 
    TimingCurves::LINEAR, 
    TimingCurves::INSTANT, 
    TimingCurves::LINEAR, 
    {{ Trigger::PRESSURE, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
};

const step rampDown = {
    1, 
    1.1, 
    1.1, 
    1.1, 
    TimingCurves::LINEAR, 
    TimingCurves::INSTANT, 
    TimingCurves::LINEAR, 
    {{ Trigger::PRESSURE, TriggerThreshold::EXACT }, { Trigger::TIME, TriggerThreshold::ABOVE }},
};

const step exampleProfile[] = {
    preInfusion, rampUp, rampDown
};