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
# sets Blynk mobile app widget colors
########
*/
// arduino libraries
#include <Arduino.h>

// my libraries
#include "growss.h"
#include "growss_blynk.h"
#include "hi_low_values.h"
#include "check_alarms.h"
#include "control.h"

// set blynk app alarm widget/led color
String BlynkLeds::set_blynk_alarm_led_color(bool alarmIsOn){
    String blynkLedColorVar;
    // set temp led color
    if(alarmIsOn) {
        blynkLedColorVar = BLYNK_RED;
    }
    else
    {
        blynkLedColorVar = BLYNK_GREEN;
    }
    return blynkLedColorVar;
}

/****************************************************************/
// set blynk app widget/led color
String BlynkLeds::set_blynk_moist_alarm_led_color(String moistAlarmStatus) {
    // --------------------------------------------------------------------
    // Check if there is a soil moisture alarm
    //   Here are suggested sensor values:
    //       Min  Typ  Max  Condition
    //       0    0    0    sensor in open air
    //       0    20   300  sensor in dry soil
    //       300  580  700  sensor in humid soil
    //       700  940  950  sensor in water

    // Human Readable Sensor values: 
    // Values  Condition
    // --------------------------
    // 0-17    "AIR"
    // 18-424  "DRY"
    // 425-689 "HUMID"
    // 690+    "WATER"

    // set moisture1 led color
    String moistBlynkLedColorVar;
    if(moistAlarmStatus == "AIR") {
        moistBlynkLedColorVar = BLYNK_ORANGE; //  LED is ORANGE on blynk app
    }
    else if(moistAlarmStatus == "DRY") {
        moistBlynkLedColorVar = BLYNK_YELLOW;   // LED is YELLOW on blynk app
    }
    else if(moistAlarmStatus == "PERFECT") {
        moistBlynkLedColorVar = BLYNK_GREEN;   // LED is Green on blynk app
    }
    else if(moistAlarmStatus == "WATER") {
        moistBlynkLedColorVar = BLYNK_STEEL_BLUE;   // LED is Steel blue on blynk app
    }
    else {
        moistBlynkLedColorVar = BLYNK_ORANGE; //  LED is ORANGE on blynk app
    }        
    return moistBlynkLedColorVar;
}

/****************************************************************/
// set blynk app on/off widget/led color
String BlynkLeds::set_blynk_on_led_color(bool alarmIsOn){
    String blynkLedColorVar;
    // set temp led color
    if(alarmIsOn) {
        blynkLedColorVar = BLYNK_BLACK;
    }
    else
    {
        blynkLedColorVar = BLYNK_GREEN;
    }
    return blynkLedColorVar;
}
