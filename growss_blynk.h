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
# classes & methods for the Blynk mobile app
########
*/
#pragma once

#ifndef _GROWSS_BLYNK_H_
#define _GROWSS_BLYNK_H_

#include <Arduino.h>

// my libraries
#include "hi_low_values.h"
#include "check_alarms.h"
#include "growss_setup.h"
#include "control.h"
// #include "growss.h"

// Blynk virtual write pins
#define BLYNK_TIME V0  // time value
#define BLYNK_TEMP V1  // temp value
#define BLYNK_HUMID V2  // humidity value
#define BLYNK_MOISTURE1 V3  // moisture1 value
#define BLYNK_MOISTURE2 V4  // pressure2 value
#define BLYNK_PRESS V5  // pressure value
#define BLYNK_HI_TEMP_VALUE V6  // hi temp value
#define BLYNK_LO_TEMP_VALUE V7  // lo temp value
#define BLYNK_HI_HUMID_VALUE V8  // hi humidity value
#define BLYNK_LO_HUNMID_VALUE V9  // low humidity value
#define BLYNK_HI_MOIST1_VALUE V10  // hi moisture1 value
#define BLYNK_LO_MOIST1_VALUE V11 // lo moisture1 value
#define BLYNK_HI_MOIST2_VALUE V12 // hi moisture2 value
#define BLYNK_LO_MOIST2_VALUE V13 // lo moisture2 value
#define BLYNK_HI_TEMP_ALARM_VALUE V14 // hi temp alarm value
#define BLYNK_LO_TEMP_ALARM_VALUE V15 // lo temp alarm value
#define BLYNK_HI_HUMID_ALARM_VALUE V16 // hi humid alarm value
#define BLYNK_LO_HUMID_ALARM_VALUE V17 // lo humid alarm value
#define BLYNK_MOIST1_ALARM V18 // soil is either: AIR, DRY, PERFECT, WATER
#define BLYNK_MOIST2_ALARM V19 // soil is either: AIR, DRY, PERFECT, WATER
#define BLYNK_HI_DENSITY_ALARM V20 // hi density (smoke) alarm value
#define BLYNK_HI_DENSITY_LED V21 // hi density (smoke) alarm LED
#define BLYNK_EX_FAN_LED V22 // is fan on LED
#define BLYNK_LIGHT_LED V23 // is light on LED
#define BLYNK_HUMIDIFIER_LED V24 // is humidifire on LED
#define BLYNK_FAN_TEMP_SETPNT V25 // temp setpoint that turns fan on
#define BLYNK_FAN_HUMID_SETPOINT V26 // humid setpoint that turns fan on
#define BLYNK_FAN_TEMP_HYSTERESIS V32 // temp hysteresis
#define BLYNK_FAN_HUMED_HYSTERESIS V27 // humidity hysteresis
#define BLYNK_LIGHT_ON_TIME V28 // when the lights turn on
#define BLYNK_LIGHT_OFF_TIME V29 // when the lights turn off
#define BLYNK_GROWSS_ACRONYM V30 // software acronym
#define BLYNK_GROWSS_NAME V31 // software name
#define BLYNK_GROWSS_VERSION V32 // software version
#define BLYNK_GROWSS_AUTH V33 // software author
#define BLYNK_GROWSS_LIC V34 // device license

// Blynk Widget Colors
const String BLYNK_BLACK = "#000000";
const String BLYNK_GREEN = "#23C48E";
const String BLYNK_BLUE = "#04C0F8";
const String BLYNK_STEEL_BLUE = "#4682B4";
const String BLYNK_CORN_BLUE = "#6495ED";
const String BLYNK_YELLOW = "#ED9D00";
const String BLYNK_RED = "#D3435C";
const String BLYNK_DARK_BLUE = "#5F7CD8";
const String BLYNK_ORANGE = "#CC6600";
const String BLYNK_GOLD = "#FFD700";

const char BLYNK_AUTH[] = "9f4faa38d423494fb9c711144e5fea1f";

class BlynkLeds {
    public:
        String tempBlynkLedColor;   // temperature alarm Blynk led color
        String humidBlynkLedColor;  // humidity alarm Blynk led color
        String densityBlynkLedColor;    // density alarm Blynk led color
        String moist1BlynkLedColor;     // color for the soil moisture alarm status
        String moist2BlynkLedColor;     // color for the soil moisture alarm status
        String lightBlynkLedColor;  // is the grow light on Blynk led color
        String exfanBlynkLedColor;  // is the exhaust fan on Blynk led color
        String humidCntrlLedColor;  // is the humidifier on Blynk led color

    // methods to set the color on the Blynk widgets
    String set_blynk_alarm_led_color(bool);
    String set_blynk_moist_alarm_led_color(String);
    String set_blynk_on_led_color(bool);
};
#endif