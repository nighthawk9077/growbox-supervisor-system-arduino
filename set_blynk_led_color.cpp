/*
########
    Nighthawk
    4.20.20
    Version: V20-20-04
    
    This project is released under The MIT License (MIT)
    Copyright 2019 Nighthawk
########

########
# checks for alarms from sensors and sets blynk led color & alarm status based on if an alarm is present
########
*/
#include "set_blynk_led_color.h"
// set blynk app alarm widget/led color
String BlynkLeds::set_blynk_alarm_led_color(bool alarmIsOn){
    String blynkLedColorVar;
    // set temp led color
    if(alarmIsOn) {
        blynkLedColorVar = BlynkLeds::BLYNK_RED;
    }
    else
    {
        blynkLedColorVar = BlynkLeds::BLYNK_GREEN;
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
        moistBlynkLedColorVar = BlynkLeds::BLYNK_ORANGE; //  LED is ORANGE on blynk app
    }
    else if(moistAlarmStatus == "DRY") {
        moistBlynkLedColorVar = BlynkLeds::BLYNK_YELLOW;   // LED is YELLOW on blynk app
    }
    else if(moistAlarmStatus == "PERFECT") {
        moistBlynkLedColorVar = BlynkLeds::BLYNK_GREEN;   // LED is Green on blynk app
    }
    else if(moistAlarmStatus == "WATER") {
        moistBlynkLedColorVar = BlynkLeds::BLYNK_STEEL_BLUE;   // LED is Steel blue on blynk app
    }
    else {
        moistBlynkLedColorVar = BlynkLeds::BLYNK_ORANGE; //  LED is ORANGE on blynk app
    }        
    return moistBlynkLedColorVar;
}

/****************************************************************/
// set blynk app on/off widget/led color
String BlynkLeds::set_blynk_on_led_color(bool alarmIsOn){
    String blynkLedColorVar;
    // set temp led color
    if(alarmIsOn) {
        blynkLedColorVar = BlynkLeds::BLYNK_BLACK;
    }
    else
    {
        blynkLedColorVar = BlynkLeds::BLYNK_GREEN;
    }
    return blynkLedColorVar;
}

