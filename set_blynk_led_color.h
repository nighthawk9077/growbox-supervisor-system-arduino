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

#ifndef _SET_BLYNK_LED_COLOR_H_
#define _SET_BLYNK_LED_COLOR_H_
#include <Arduino.h>

class BlynkLeds {
    public:
        // Blink Colors
        String BLYNK_BLACK = "#000000";
        String BLYNK_GREEN = "#23C48E";
        String BLYNK_BLUE = "#04C0F8";
        String BLYNK_STEEL_BLUE = "#4682B4";
        String BLYNK_CORN_BLUE = "#6495ED";
        String BLYNK_YELLOW = "#ED9D00";
        String BLYNK_RED = "#D3435C";
        String BLYNK_DARK_BLUE = "#5F7CD8";
        String BLYNK_ORANGE = "#CC6600";
        String BLYNK_GOLD = "#FFD700";
        String tempBlynkLedColor;   // temperature alarm Blynk led color
        String humidBlynkLedColor;  // humidity alarm Blynk led color
        String densityBlynkLedColor;    // density alarm Blynk led color
        String moist1BlynkLedColor;     // color for the soil moisture alarm status
        String moist2BlynkLedColor;     // color for the soil moisture alarm status
        String lightBlynkLedColor;  // is the grow light on Blynk led color
        String exfanBlynkLedColor;  // is the exhaust fan on Blynk led color
        String humidCntrlLedColor;  // is the humidifier on Blynk led color

        // methods
    String set_blynk_alarm_led_color(bool);
    String set_blynk_moist_alarm_led_color(String);
    String set_blynk_on_led_color(bool);
};
#endif