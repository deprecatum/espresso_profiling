#include <hardware/sensors/flow/TAB32-S21PO10C-11R.h>
#include <hardware/sensors/pressure/generic_pressure_transducer.h>
#include "hardware/sensors/temperature/ntc_100k.h"

float getFlow() {
    return getML();
};
float getPressure() {
    return getBar();
};

float getTemperature(){
    return getCelsius();
};