#include <Arduino.h>
#include <pindef.h>
#include <main.h>
#include <functionality/profiling.h>

StatusCode handleSteps (Mode mode) {
    StatusCode code = StatusCode::fail;
    for (Mode : Step) {

        // set flow; temp; pressure for Y time
        /*
        requestedTemp(target, time, curve)
        requestedFlow(target, time, curve)
        requestedPressure(target, time, curve)
        */
    }
    return StatusCode::fail;
}

void flush () {

}

StatusCode outputMode(Mode mode) {
    return handleSteps(mode);
    return StatusCode::fail;
}