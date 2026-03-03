#include <main.h>
#include <hardware/output/pump/ep5.h>   

StatusCode requestedFlow (int flow, int time, int curve) {
    // set target flow

    // apply curve

    // check target PID, if out of target return fail

    return StatusCode::fail;
}

StatusCode setFlow (int flow) {
    // set target flow

    // apply curve

    // check target PID, if out of target return fail

    return StatusCode::success;
}