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

#ifndef _CHECK_ALARMS_H_
#define _CHECK_ALARMS_H_
#include <Arduino.h>

class Alarms {
    public:
        // hardware
        bool lightIsOn;
        bool exhaustFanIsOn;
        bool humidifierIsOn;

        // alarm_status
        bool tempAlarmIsOn;
        bool humidAlarmIsOn;
        String moist1AlarmStatus;
        String moist2AlarmStatus;

        // alarm threasholds. ie at what value does the alarm go off
        float hiTempAlarmThreashold;
        float lowTempAlarmThreashold;
        float hiHumidityAlarmThreashold;
        float lowHumidityAlarmThreashold;
        float hiDensityAlarmThreashold;

        // methods
        bool check_alarm(float, float, float);
        String check_moisture_alarms(int);
};
#endif