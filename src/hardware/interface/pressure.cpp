#include <main.h>
#include <hardware/output/pump/ep5.h>
#include <hardware/sensors/sensors.h>
#include <functionality/espressoProfile.h>

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

StatusCode unsetPressure () {
    setPressure(0,0);
    return StatusCode::success;
}