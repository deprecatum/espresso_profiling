#include <Arduino.h>
#include <pindef.h>
#include <main.h>
#include <functionality/espressoProfile.h>
#include <hardware/sensors/sensors.h>
#include <hardware/interface/pressure.cpp>

struct CurveResponse {
    StatusCode statusCode;
    int actualTime;
    float actualFlow;
};

StatusCode handleMeasurementThreshold (Trigger trigger, TriggerThreshold threshold, float measurement, float measurementTargetBottom, float measurementTargetTop, StatusCode(*unsetFunction)(void)) {
    switch (threshold) {
        case TriggerThreshold::ABOVE: {
            if (measurement > measurementTargetTop) return unsetFunction();
            break;
        }
        case TriggerThreshold::EXACT: {
            if (measurement > measurementTargetBottom && measurement < measurementTargetTop) return unsetFunction();
            break;
        }
        case TriggerThreshold::BELOW: {
            if (measurement < measurementTargetBottom) return unsetFunction();
            break;
        }
    };
};

CurveResponse setCurve (float targetBar, int time, TimingCurves curve, Trigger trigger, TriggerThreshold threshold) {
    boolean isSettingCurve = true;
    // time
    int startingTime = millis();
    int currentTime = startingTime;
    // pressure
    float targetTop = targetBar + TOP_MARGIN;
    float targetBottom = targetBar - BOTTOM_MARGIN;
    float actualFlow = 0.0;
    CurveResponse response = { statusCode: StatusCode::success, actualTime: startingTime, actualFlow: actualFlow };
    
    while (isSettingCurve) {
        float pressure = getPressure();
        currentTime = millis();
        float timePercentage = (currentTime - startingTime) / time;
        if (trigger == Trigger::MEASUREMENT) {
            handleMeasurementThreshold(trigger, threshold, pressure, targetBottom, targetTop, unsetPressure);
        }

        // set pressure to target bar
        // turn on SSR mosfet to specified PWM
        response.statusCode = setPressure(targetBar, (curveFunction(timePercentage, curve) ));
        response.actualTime = currentTime - startingTime; 
        if (response.statusCode != StatusCode::success) {
            unsetPressure();
            isSettingCurve = false;
        } 
    }

    // adjust pwm and maintain target tem
    return response;
}