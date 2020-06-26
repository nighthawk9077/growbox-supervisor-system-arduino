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
#########
*/
#include <Arduino.h>

class Enable_features{
    public:
        bool debug = false; // don't print debugging values during execution
        bool email = false; // email enable - True turns on email alerts
        bool sms = false; // sms text enable - True sends text alart to mobile phone
        bool exhaust_fan = true; // enable controlling the fan - True allows arduino to control fan
        bool humidity = true; // control the humidifier - allow arduino to control the water atomizer/humidifier
        bool hum_dehumid = true; // either use the humidifier or use the de-humdifier
        bool light = true; // enable controlling the light - True allows arduino to control the lights
};

/****************************************************************/
// time class
class Growss_time {
    public:
        bool setTime;
        int hour;
        int min;
        int sec;
        int year;
        int month;
        int dayOfMonth;
        String date;
        String time;
        String dateTime;
};

class Growss_data {
    public:
        float temp;
        float humidity;
        float pressure;
        int moisture1;
        int moisture2;
};

void growss_welcome();

