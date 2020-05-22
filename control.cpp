/*
########
    Nighthawk
    4.20.20
    Version: V20-20-04
    
    This project is released under The MIT License (MIT)
    Copyright 2019 Nighthawk
########

########
# controls the hardware
########
*/
#include "control.h"
#include "growss.h"

// turns on exhaust fan (relay) if values are above threashold.
// turns off exhaust fan (relay) if values are below threshold
bool Exhaust_fan::exhaust_fan_cntrl(float growssTemp, float growssHumidity, float temp_setpoint, float temp_hysteresis, float humid_setpoint, float humid_hysteresis) {
    bool exFanIsOnVar;
    // Turn Fan on if temperature or humidity is too high
    if ((growssTemp > (temp_setpoint + temp_hysteresis) or (growssHumidity > humid_setpoint + humid_hysteresis))) {
        // turn on exhaust fan. fan is using nc side of relay (always on during reset), so logic is inverted
        digitalWrite(EXHAUST_FAN, LOW); // turn on exhaust fan     
        exFanIsOnVar = 1; 
      }
    // exhaust fan stays on until both temp & humidity reaches bottom end of setpoint
    else if ((growssTemp < (temp_setpoint - temp_hysteresis) || (growssHumidity < humid_setpoint - humid_hysteresis))) {
        // turn off exhaust fan. fan is using nc side of relay, so logic is inverted
        digitalWrite(EXHAUST_FAN, HIGH); // turn off exhaust fan   
        exFanIsOnVar = 0; 
    }
    return exFanIsOnVar;
}

/****************************************************************************/
// turn on the light (relay) if time is between time on & time off.
// this code doesn't work if light is to be on crossing midnite (hour 24)
bool Light::light_cntrl(int hourNow, int lightOnTimeHour, int lightOffTimeHour){
    bool lightIsOnVar;
    // Turn on/off lights at a certain time
    if ( hourNow >= lightOnTimeHour && hourNow <= lightOffTimeHour) {
        // turn on grow lights using nc side of relay (lights on during reset), so logic is inverted
        digitalWrite(LIGHT, LOW);     // turn on grow light
        lightIsOnVar = 1;
    }
    else {
        // turn off grow lights:: lights using nc side of relay, so logic is inverted
        digitalWrite(LIGHT, HIGH);     // turn off grow light
        lightIsOnVar = 0; // light is off
    }
    return lightIsOnVar;
}

/****************************************************************************/
// turns on humidifier (relay) if values are below threashold.
// turns off humidifier (relay) if values are above threshold
bool Humid_Cntrl::humid_cntrl(float growssHumidity, float humiditySetpoint, float humidityHisteresis) {    
    bool humidCntrIsOnVar;
    // turn on humidifier if humidity is too low
    if (growssHumidity < (humiditySetpoint -  humidityHisteresis)) {
        // humidifier is using no side of relay, so humidifer is always off during reset
        digitalWrite(HUMIDIFIER, HIGH);     // turn on humidifier 
        humidCntrIsOnVar = 1; // humidifier is on
    }
    if (growssHumidity > (humiditySetpoint +  humidityHisteresis)) {
        digitalWrite(HUMIDIFIER, LOW);     // turn off humidifier 
        humidCntrIsOnVar = 0; // humidifier is off
    }
    return humidCntrIsOnVar;
}
