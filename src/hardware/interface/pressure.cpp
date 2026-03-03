#include <main.h>
#include <hardware/output/pump/ep5.h>
#include <hardware/sensors/sensors.h>
#include <functionality/profiling.h>

#define MAX_BAR 12.0F
#define MARGIN 0.25F
#define TOP_MARGIN MARGIN
#define BOTTOM_MARGIN MARGIN

StatusCode unsetPressure () {
    setPressure(0,0);
    return StatusCode::success;
}

// set pressure to target bar
StatusCode setPressure (float targetBar, float targetPWM) {
    float pressure = getPressure();
    StatusCode statusCode = StatusCode::success;

    // turn SSR mosfet to specified PWM
    
    // over pressure
    if (pressure > MAX_BAR) {
        statusCode = StatusCode::failedOnRead;
    }
    // adjust pwm and maintain target pressure
    return statusCode;
}

// set pressure to target bar
StatusCode setPressureCurve (float targetBar, int time, TimingCurves curve, Trigger trigger, TriggerThreshold threshold) {
    int previousTime = millis();
    int currentTime = previousTime;
    boolean isSettingCurve = true;
    float targetTop = targetBar + TOP_MARGIN;
    float targetBottom = targetBar - BOTTOM_MARGIN;
    StatusCode statusCode = StatusCode::success;
    
    while (isSettingCurve) {
        float pressure = getPressure();
        currentTime = millis();
        float timePercentage = (currentTime - previousTime) / time;
        if (trigger == Trigger::MEASUREMENT) {
            handleMeasurementThreshold(trigger, threshold, pressure, targetBottom, targetTop, unsetPressure);
        }

        // exceeded alotted time, stop function
        if (currentTime - previousTime > time) {
            //set curve to 0
            return unsetPressure();
        }
        // turn on SSR mosfet to specified PWM
        statusCode = setPressure(targetBar, (curveFunction(timePercentage, curve) ));
        if (statusCode != StatusCode::success) return statusCode;
    }

    // adjust pwm and maintain target tem
    return statusCode;
}