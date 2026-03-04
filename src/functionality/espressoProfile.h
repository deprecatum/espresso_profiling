#include <Arduino.h>
#include <main.h>

enum class TimingCurves {
  EASE_IN,
  EASE_OUT,
  EASE_IN_OUT,
  LINEAR,
  INSTANT,
};

enum class Trigger {
    TIME,
    MEASUREMENT
};

enum class TriggerThreshold {
    ABOVE,
    BELOW,
    EXACT,
};

struct Flag {
    Trigger trigger;
    TriggerThreshold Threshold;
};

struct Step {
    // seconds
    int time;
    // ML/s
    float requestedFlow;
    // Celsius
    float requestedTemp;
    // BAR
    float requestedPressure;
    TimingCurves flowCurve;
    TimingCurves tempCurve;
    TimingCurves pressureCurve;
    // go to next Step based on flags
    Flag flags[];
};

enum OperationMode : int {
    singleExtraction = 0L,
    doubleExtraction = 1L,
    flush = 2L,
    outputSteam = 3
};

// percentage is given from 0.00 to 1.0, to be plotted against time from 0 to X
float curveFunction (float percentage, TimingCurves curve) {
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