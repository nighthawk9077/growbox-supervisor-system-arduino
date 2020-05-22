/*
########
    Nighthawk
    4.20.20
    Version: V20-20-04
    
    This project is released under The MIT License (MIT)
    Copyright 2019 Nighthawk
########

########
# classes & methods
########
*/
#pragma once

#ifndef _CONTROL_H_
#define _CONTROL_H_
#include <Arduino.h>
// exhaust fan control class & methods
class Exhaust_fan{
    public:
        float tempSetpoint; // temp set point when fan turns on. value changes depending on day or nite
        float dayTemp; // temp set point when lights are on
        float niteTemp; // temp set point when lights are off
        float tempHysteresis; // temp range the fan turns on and off
        float humidSetpoint; // humidity set point when fan turns on
        float humidHysteresis; // humid range the fan turns on and off
        bool exFanIsOn; // flag indicates when exhaust fan is on

        // methods
        bool exhaust_fan_cntrl(float, float, float, float, float, float);

};

/****************************************************************/
// grow light class & methods
class Light
{   public:
        int lightOnHour; // hour when the lights are turned on
        int lightOnMinute;  // min when the lights are turned on
        int lightOffHour; // hour when the lights are turned off
        int lightOffMinute; // minute when the lights are turned off
        bool lightIsOn; // flag indicates when light is on
        
        // methods
        bool light_cntrl(int, int, int);
};

/****************************************************************/
// humidifier control classes & methods
class Humid_Cntrl {
    public:
        float humiditySetpoint;
        float humidityHysteresis;
        bool humidifierIsOn;
    
    // methods
        bool humid_cntrl(float, float, float);

};
#endif