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
#include <Arduino.h>
#include "growss_setup.h"

void setup_atmega2560() {
    // setup ATMega pins
    pinMode(EXHAUST_FAN, OUTPUT); // exhaust fan relay  
    pinMode(HUMIDIFIER, OUTPUT);     // humidifier relay
    pinMode(LIGHT, OUTPUT);     // grow light relay
    pinMode(BUZZER, OUTPUT);    
    pinMode(HUMIDIFIER, OUTPUT);    // humidifier control
    pinMode(AIRFLOW_FAN, OUTPUT);
    
    // add analog pins
    pinMode(MOISTURE1, INPUT);  // soil moisture sensor #1
    pinMode(MOISTURE2, INPUT);  // soil moisture sensor #2
    pinMode(DENSITY, INPUT);    // mq2 air/density sensor
}

