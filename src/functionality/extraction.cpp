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
    return code;
}

void flush () {

}

StatusCode outputMode(Mode mode) {
    switch (mode) {
        case Mode::singleExtraction:
        case Mode::doubleExtraction: 
        case Mode::flush:
        {
            return handleSteps(mode);
        }
        default: {
            return StatusCode::fail;
            break;
        }
    }
}