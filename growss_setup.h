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

#pragma once

#ifndef _GROWSS_SETUP_H_
#define _GROWSS_SETUP_H_

// Arduino base Hat Digital Pin numbers
// #define DEHUMIDIFIER 0 // de-humidifier (SPDT Relay) digital port
#define MOISTURE1 A0 // moisture sensor #1 analog port
#define MOISTURE2 A1 // moisture sensor #2 analog port
#define DENSITY A3 // mq2 air/density sensor
#define LIGHT 4 // light (SPDT Relay) digital port
#define EXHAUST_FAN 5 // exhaust fan (SPDT Relay) digital port
#define BUZZER 7 // buzzer for alarms and power on test
#define HUMIDIFIER 8 // humidifier (SPDT Relay) digital port
#define AIRFLOW_FAN 9 // airflow fan (SPDT) Relay) digital port

// GROWSS Version Information
#define GROWSS_NAME1 "GROWSS"
#define GROWSS_NAME2 "The GROWbox Supervisor System"
#define GROWSS_VER "20-04-20-ARDUINO"
#define GROWSS_AUTH "NIGHTHAWK/THE CANNABIS REVIEWER"
#define GROWSS_LIC "2020 MIT"

// SMS email & text alert settings
#define GROWSS_EMAIL_SERVER = "smtp.gmail.com"
#define GROWSS_EMAIL_PORT = 587;
#define GROWSS_EMAIL_ADDR = "Your GROWSS email address Here"
#define GROWSS_EMAIL_PWD = "Your GROWSS email password Here"
#define GROWSS_EMAIL_SENDER_ADDR = "The sending email address Here"
#define GROWSS_TEXT_NUMBER = "1231231234@vtext.com"

void setup_atmega2560();
#endif
