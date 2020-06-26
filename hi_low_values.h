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

########
# classes & methods
########
*/
#pragma once

#ifndef _GET_HI_LOW_VALUES_H_
#define _GET_HI_LOW_VALUES_H_

class Hi_lows {
    public:
        float hiTemp;
        float lowTemp;
        float hiHumidity;
        float lowHumidity;
        float hiPressure;
        float lowPressure;

        int hiMoisture1;
        int lowMoisture1;
        int hiMoisture2;
        int lowMoisture2;

        // methods
        float setHiValue(float, float);
        float setLowValue(float, float);

        int setHiMoisture(int, int);
        int setLowMoisture(int, int);
};
#endif