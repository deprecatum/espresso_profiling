#include <hardware\input\flow\TAB32-S21PO10C-11R.h>
#include <hardware\input\pressure\generic_pressure_transducer.h>
#include "hardware\input\temp\ntc_100k.h "

void startSensors () {

}

float getFlow() {
    return getML();
};
float getPressure() {
    return getPSI();
};

float getTemperature(){
    return getCelsius();
};