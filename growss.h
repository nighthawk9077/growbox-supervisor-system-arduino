/*
    Nighthawk
    4.20.20
    Version: V20-20-04
    
    This project is released under The MIT License (MIT)
    Copyright 2019 Nighthawk

    Constants & structures file
*/
#include <Arduino.h>

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

/* // Blynk virtual pins
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
#define BLYNK_HI_TEMP_ALARM V14 // hi temp alarm value
#define BLYNK_LO_TEMP_ALARM V15 // lo temp alarm value
#define BLYNK_HI_HUMID_ALARM V16 // hi humid alarm value
#define BLYNK_LO_HUMID_ALARM V17 // lo humid alarm value
#define BLYNK_MOIST1_ALARM V18 // soil is either: AIR, DRY, PERFECT, WATER
#define BLYNK_MOIST2_ALARM V19 // soil is either: AIR, DRY, PERFECT, WATER
#define BLYNK_HI_DENSITY_ALARM V20 // hi density (smoke) alarm value
#define BLYNK_HI_DENSITY_LED V21 // hi density (smoke) alarm LED
#define BLYNK_EX_FAN_LED V22 // is fan on LED
#define BLYNK_LIGHT_LED V23 // is light on LED
#define BLYNK_HUMIDIFIER_LED V24 // is humidifire on LED
#define GROWSS_ACRONYM V25 // software acronym
#define GROWSS_NAME V26 // software name
#define GROWSS_VERSION V27 // software version
#define GROWSS_AUTH V28 // software author
#define GROWSS_LIC V29 // device license
#define BLYNK_FAN_TEMP_SETPNT V30 // temp setpoint that turns fan on
#define BLYNK_FAN_HUMID_SETPOINT V31 // humid setpoint that turns fan on
#define BLYNK_FAN_TEMP_HYSTERESIS V32 // temp hysteresis
#define BLYNK_FAN_HUMED_HYSTERESIS V33 // humidity hysteresis
#define BLYNK_LIGHT_ON_TIME V34 // when the lights turn on
#define BLYNK_LIGHT_OFF_TIME V35 // when the lights turn off
 */


// SMS email & text alert settings
#define GROWSS_EMAIL_SERVER = "smtp.gmail.com"
#define GROWSS_EMAIL_PORT = 587;
#define GROWSS_EMAIL_ADDR = "Your GROWSS email address Here"
#define GROWSS_EMAIL_PWD = "Your GROWSS email password Here"
#define GROWSS_EMAIL_SENDER_ADDR = "The sending email address Here"
#define GROWSS_TEXT_NUMBER = "1231231234@vtext.com"

/****************************************************************/
// Enable flags - Enable debugging, email, & other features
struct Enable_features
{
    bool debug = false; // don't print debugging values during execution
    bool email = false; // email enable - True turns on email alerts
    bool sms = false; // sms text enable - True sends text alart to mobile phone
    bool to_file = false; // True allows data to be saved to local disk
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
};

void growss_welcome();

