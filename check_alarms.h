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

        // methods
        bool check_alarm(float, float, float);
        String check_moisture_alarms(int);
};
#endif