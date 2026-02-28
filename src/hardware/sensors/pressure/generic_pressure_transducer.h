#include <Arduino.h>
#include <pindef.h>
// pressure sensor 500 psi
// v        psi
// 0.5       0
// 1,1745    130.5
// 3.3       366,67
// 4.5       500
// per v 125 psi

const int psiPerADC = 366.67/4096;

float getPSI () {
    return ceil(620 - analogRead(PRESSURE_SENSOR)) * psiPerADC;
}
