void computePID(double Kp, double Ki, double Kd) {
    unsigned long lastTime;
    double Input, Output, Setpoint;
    double errSum, lastErr;

    /*How long since we last calculated*/
    unsigned long now = millis();
    double timeChange = (double)(now - lastTime);
    
    /*Compute all the working error variables*/
    double error = Setpoint - Input;
    errSum += (error * timeChange);
    double dErr = (error - lastErr) / timeChange;
    
    /*Compute PID Output*/
    Output = Kp * error + Ki * errSum + Kd * dErr;
    
    /*Remember some variables for next time*/
    lastErr = error;
    lastTime = now;
}