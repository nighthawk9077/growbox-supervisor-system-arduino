/*
########
# The GROWbox Supervisor System (GROWSS)
# Nighthawk
# 4.20.20
#
# This project is released under The MIT License (MIT)
# Copyright 2020 Nighthawk
#
# Version: V20-04-20-V1B (Arduino Version):
        - beta version #1
        - works with bme280, moisture sensors, real time clock
        - has debug hooks, but not conforming to arduino debugging method yet
        - No Blynk implimentation yet

# Version: V20-07-01-V2B-V2B:
        - beta version #2
        - added Blynk mobile virtual pin reads (from arduino to mobile app)
        - renamed files and consolidated code to better work with Blynk
        - Code compiles but has not been tested with the Blynk mobile app yet
            - got to get local server configured for an additional device & design new Blynk mobile app
########
*/
#include "growss.h"
#include "hi_low_values.h"

// sets the high value
float Hi_lows::setHiValue(float growssValue, float hiValue ) {
    float hiValueVar;
    // set temp hi value
    if (growssValue > hiValue) {
        hiValueVar = growssValue;
    }
    else
    {
        hiValueVar = hiTemp;
    }
    // if( enable_features.debug) {
    //     Serial.print("current hi_low_values is: "); 
    //     Serial.println(growssValue);
    //     Serial.print("hi value is: "); 
    //     Serial.println(hiValue);
    //     Serial.println("set hi value funct done.\n");
    // }
    return hiValueVar;
}

/****************************************************************/
// sets the low value
float Hi_lows::setLowValue(float growssValue, float lowValue){
    float lowValueVar;
    // set temp low value
    if (growssValue < lowValue) {
        lowValueVar = growssValue;
    }
    else
    {
        lowValueVar = lowValue;
    }
    // if( enable_features.debug) {
    //     Serial.print("current value is: "); 
    //     Serial.println(growssValue);
    //     Serial.print("low value is: "); 
    //     Serial.println(lowValueVar);
    //     Serial.println("set low value funct done.\n");
    // }
    return lowValueVar;
}

/****************************************************************/
// sets hi soil moisture value
int Hi_lows::setHiMoisture(int growssMoisture, int hiMoisture) {
    int hiMoistureVar;
    // set moisture low value
    if (growssMoisture > hiMoisture) {
        hiMoistureVar = growssMoisture;
    }
    else
    {
        hiMoistureVar = hiMoisture;
    }
    // if( enable_features.debug) {
    //     Serial.print("current moisture1 is: "); 
    //     Serial.println(growssMoisture1);
    //     Serial.print("low moisture1 is: "); 
    //     Serial.println(lowMoisture1);
    //     Serial.println("moisture1 low done.\n");
    // }
    return hiMoistureVar;
}

/****************************************************************/
// sets low soil moisture value
int Hi_lows::setLowMoisture(int growssMoisture, int lowMoisture) {
    int lowMoistureVar;
    // set moisture low value
    if (growssMoisture < lowMoisture) {
        lowMoistureVar = growssMoisture;
    }
    else
    {
        lowMoistureVar = lowMoisture;
    }
    // if( enable_features.debug) {
    //     Serial.print("current moisture1 is: "); 
    //     Serial.println(growssMoisture1);
    //     Serial.print("low moisture1 is: "); 
    //     Serial.println(lowMoisture1);
    //     Serial.println("moisture1 low done.\n");
    // }
    return lowMoistureVar;
}

