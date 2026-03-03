/*
    ULKA EP5 solenoid pump
    datasheet: https://cdn.shopify.com/s/files/1/0503/8833/6813/files/E_high_pressure.pdf?v=1726665265
    
    // 48 watts at 230 vac
    flow rate
    0 bar - 650
    6 bar - 350
    10 bar - 210
*/

// get ML in relation to bars
float pressureFunctionBar (float Bar) {
    return (-40*Bar) + 612;
}