/*
########
# The GROWbox Supervisor System (GROWSS)
# Version: V20-04-20-V1B (Arduino Version)
# Nighthawk
# 4.20.20
#
# This project is released under The MIT License (MIT)
# Copyright 2020 Nighthawk
########

########
# monitors and controls hardware in a grow box or grow cabinet
########

########
# The GROWbox Supervisor System (GROWSS) is a monitoring & control system for small to medium grow boxes
# & grow cabinets. GROWSS uses an Arduino ATMega2560 SBC, a Grove Base Hat, & Grove Sensors to monitor and
# control the growing environment.
#
# Features Include:
#    - Monitor Temperature, Humidity, Density (smoke alarm) & soil moisture.  Measurements are taken
#        about every 25 seconds and updated to the displays (below).
#    - Controls growing lights, exhaust fan, & humidifier.
#       - Turns lights on & off based on time.
#       - Turns exhaust fan on & off based on either day (lights on) or nite (lights off) temp & humidity.
#       - Turns water atomizer (humidifier) on & off based on humidity.
#    - Sets alarms for hi/low temperature, humidity & soil moisture.  Sets alarm if there is smoke.
#    - Monitoring & Alarm information is provided many ways:
#       - A mobile app is also available to monitor the growing environment with alarms & hi/low values.
#       - Send email and/or text if an alarm is present.
#       - Enable/Disable email, text, fan, light, & atomizer (humidifier). Currently has to be changed
#           in the header file.
########

########
# Features maybe included in the future:
#   - Automatically water plant when soil moisture is too low.
#   - Ability to change alarm threasholds easily (ie. switch, etc.)
#   - Enable/Disable email, text, fan, light, & atomizer (humidifier) from Blynk app.
#   - Retain values after a crash or reboot.
#   - Catching more errors to avoid program crash from broken sensors, etc.
########

########
#Grove Base Hat Pinout Definitions

#   Port #  Pins on Port #  Type                Sensor Pin  Sensor/Module
#   ------------------------------------------------------------------------
#   D2      D2 & D3         DIGITAL             D2          Open
#   D3      D3 & D4         DIGITAL             D3          Open                                           
#   D4      D4 & D5         DIGITAL             D4          Grove - 2-Channel SPDT Switch 1, LED Lights
#   D5      D5 & D6         DIGITAL             D5          Grove - 2-Channel SPDT Switch 2, Exhaust Fan
#   D6      D6 & D7         DIGITAL             D6          n/a
#   D7      D7 & D8         DIGITAL             D7          Grove Buzzer
#   D8      D8 & D9         DIGITAL             D8          Grove - 2-Channel SPDT Switch 1, Humidifier
#                                               D9          Grove - 2-Channel SPDT Switch 1, Air Flow Fan               
#   A0      A0 & A1         ANALOG              A0          Grove - Moisture #1 Sensor
#   A1      A1 & A2         ANALOG              A1          Grove - Moisture #2 Sensor
#   A2      A2 & A3         ANALOG              A3          Grove MQ2 Air Sensor

#   I2C-1   I2C                                             BME280 Temp, Humid, Press, Alt sensor
#   I2C-2   I2C                                             Open
#   I2C-3   I2C                                             Open
#   I2C-4   I2C                                             Open
########
*/
#include <Arduino.h>
#include "growss.h"
#include "hi_low_values.h"
#include "check_alarms.h"
#include "control.h"
#include "set_blynk_led_color.h"
#include "Seeed_BME280.h"
#include <Wire.h>
//#include <SPI.h>
//#include <Ethernet.h>
#include "PCF85063TP.h"
//#include <BlynkSimpleEthernet.h>

PCD85063TP RTclock;// instantiate clock object
BME280 bme280;  // instantiate bme280 object

// Define Structures
Growss_time growss_time; 
Enable_features enable_features; // flags to enable features 
float growssTemp;   // temperature read from the bme280
float growssHumidity;    // humidity read from the bme280
float growssPressure;    // presser read from bme280
int growssMoisture1;    // soil moisture #1 is read
int growssMoisture2;    // soil moisure #2 is read
Hi_lows hi_lows;  // the high & low values of the day
Alarms alarms;  // what alarms are there?
Light light;  // led light settings
Exhaust_fan exhaust_fan;  // the exhuast fan variables
Humid_Cntrl humidity_cntrl;  // control the humidifier/dehumidifier
BlynkLeds blynkLeds; // the color of the blynk mobil app leds & widgets

/****************************************************************************/
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);
    // setup ATMega pins
    pinMode(EXHAUST_FAN, OUTPUT); // exhaust fan relay  
    pinMode(HUMIDIFIER, OUTPUT);     // humidifier relay
    pinMode(LIGHT, OUTPUT);     // grow light relay
    // add analog pins

    // initialize bme280
    if(!bme280.init()){
      Serial.println("Device error!");
    }

    // growss_welcome();
    enable_features.debug = 1; //turn on debugging
    growss_time.setTime = 0;  // set the time if the flag is 1

    // light control variables
    light.lightOnHour = 9; // 9am
    light.lightOnMinute = 0;
    light.lightOffHour = 20; // 9pm
    light.lightOffMinute = 0;

    // exhaust fan variables
    exhaust_fan.dayTemp = 90.0; // temp set point when lights are on
    exhaust_fan.niteTemp = 80.0; // temp set point when lights are off
    exhaust_fan.tempHysteresis = 0.5; // temp range the fan turns on and off
    exhaust_fan.humidSetpoint = 80.0; // humidity set point when fan turns on
    exhaust_fan.humidHysteresis = 0.5; // humid range the fan turns on and off

    // alarm variables
    alarms.hiTempAlarmThreashold = 85.0;
    alarms.lowTempAlarmThreashold = 54.0;
    alarms.hiHumidityAlarmThreashold = 90.0;
    alarms.lowHumidityAlarmThreashold = 40.0;

    // humidity control variables
    humidity_cntrl.humiditySetpoint = 50.0;
    humidity_cntrl.humidityHysteresis = 0.5;

    // start clock
    RTclock.begin();
    delay(1000);
    // set time
    if (growss_time.setTime) {
      RTclock.stopClock();
      RTclock.fillByYMD(2020,9,17);//yy/m/d
      RTclock.fillByHMS(20,41,00);//15:28 30"
      RTclock.fillDayOfWeek(SUN);//Saturday
      RTclock.setTime();//write time to the RTC chip
      RTclock.startClock();
    }

    //clock.setcalibration(1, 32767.2);  // Setting offset by clock frequency
    uint8_t ret = RTclock.calibratBySeconds(0, -0.000041);
    Serial.print("offset value: ");
    Serial.print("0x");
    Serial.println(ret, HEX);
    
    // get current bme280 values
    growssTemp = (9/5) * bme280.getTemperature() + 32; //convert to deg f
    growssTemp = 1.5107*(growssTemp) - 14.541;    // calibrate temp
    growssHumidity = bme280.getHumidity();
    growssHumidity = (0.8223 * growssHumidity + 15.386);  // calibrate humidity
    growssPressure = bme280.getPressure();

    // get current soil moisture values
    growssMoisture1 = analogRead(MOISTURE1);
    growssMoisture2 = analogRead(MOISTURE2);

    // set the current values as the baseline hi & low values
    hi_lows.hiTemp = growssTemp;
    hi_lows.lowTemp = growssTemp;
    hi_lows.hiHumidity = growssHumidity;
    hi_lows.lowHumidity = growssHumidity;
    hi_lows.hiPressure = growssPressure;
    hi_lows.lowPressure = growssPressure;
    // moisture values
    hi_lows.hiMoisture1 = growssMoisture1;
    hi_lows.lowMoisture1 = growssMoisture1;
    hi_lows.hiMoisture2 = growssMoisture2;
    hi_lows.lowMoisture2 = growssMoisture2;

    Serial.print("setup funct baseline growssTemp is: "); 
    Serial.println(growssTemp);
    Serial.print("setup funct baseline hi temp is: "); 
    Serial.println(hi_lows.hiTemp);
    Serial.print("setup funct baseline low temp is: "); 
    Serial.println(hi_lows.lowTemp);
    Serial.println("setup funct temp hi_lows debug done.");
    Serial.println("setup funct done\n");
}

// the loop function runs over and over again forever
void loop() {
  // get current time
  RTclock.getTime();
  growss_time.hour = RTclock.hour;
  growss_time.min = RTclock.minute;
  growss_time.sec = RTclock.second;
  growss_time.year = RTclock.year;
  growss_time.month = RTclock.month;
  growss_time.dayOfMonth = RTclock.dayOfMonth;
  // print the current time
  Serial.print("Current Time is: ");
  Serial.print(growss_time.hour, DEC);
  Serial.print(":");
  Serial.print(growss_time.min, DEC);
  Serial.print(":");
  Serial.println(growss_time.sec, DEC);
  Serial.print(growss_time.month, DEC);
  Serial.print("/");
  Serial.print(growss_time.dayOfMonth, DEC);
  Serial.print("/");
  Serial.println(growss_time.year + 2000, DEC);

  
  // get current bme280 values
  growssTemp = ((9 / 5) * bme280.getTemperature() + 32); //convert to deg f
  growssTemp = 1.5107 * growssTemp - 14.541;  // calibrate temp
  growssHumidity = bme280.getHumidity();
  growssHumidity = (0.8223 * growssHumidity + 15.386);  // calibrate humidity

  growssPressure = bme280.getPressure() * 0.00029530;
  if (enable_features.debug) {
    Serial.println("------ BME280 VALUES ------ ");
    Serial.print("growss.ino cur temp value is: ");
    Serial.println(growssTemp);
    Serial.print("growss.ino cur humid value is: ");
    Serial.println(growssHumidity);
    Serial.print("growss.ino cur pressure value is: ");
    Serial.println(growssPressure);
  }

  // get current soil moisture values
  growssMoisture1 = analogRead(MOISTURE1);
  growssMoisture2 = analogRead(MOISTURE2);
  if( enable_features.debug) {
    Serial.println("------ MOISTURE VALUES ------ ");
    Serial.print("growss.ino moisture1 value: ");
    Serial.println(growssMoisture1);
    Serial.print("growss.ino moisture2 value: ");
    Serial.println(growssMoisture2);
  }
  delay(3000);

/****************************************************************************/
  // get hi & low temp values
  hi_lows.hiTemp = hi_lows.setHiValue(growssTemp, hi_lows.hiTemp);
  hi_lows.lowTemp = hi_lows.setLowValue(growssTemp,  hi_lows.lowTemp);

  // get hi & low humidity values
  hi_lows.hiHumidity = hi_lows.setHiValue(growssTemp, hi_lows.hiHumidity);
  hi_lows.lowHumidity = hi_lows.setLowValue(growssTemp, hi_lows.lowHumidity);

  // get hi & low pressure values
  hi_lows.hiPressure = hi_lows.setHiValue(growssPressure, hi_lows.hiPressure);
  hi_lows.lowPressure = hi_lows.setLowValue(growssPressure, hi_lows.lowPressure);

  // get hi & low soil moisture #1 values
  hi_lows.hiMoisture1 = hi_lows.setHiMoisture(growssMoisture1, hi_lows.hiMoisture1);
  hi_lows.lowMoisture1 = hi_lows.setLowMoisture(growssMoisture1, hi_lows.lowMoisture1);

  // get hi & low soil moisture #2 values
  hi_lows.hiMoisture2 = hi_lows.setHiMoisture(growssMoisture2, hi_lows.hiMoisture2);
  hi_lows.lowMoisture2 = hi_lows.setLowMoisture(growssMoisture2, hi_lows.lowMoisture2);
  if(enable_features.debug) {
    Serial.println("------ HI/LOW VALUES ------ ");
    Serial.print("growss.ino growssTemp is: ");
    Serial.println(growssTemp);
    Serial.print("growss.ino hi temp is: ");
    Serial.println(hi_lows.hiTemp);
    Serial.print("growss.ino low temp is: ");
    Serial.println(hi_lows.lowTemp);
  }

/****************************************************************************/
  // check for alarms
  // check temp alarm
  alarms.tempAlarmIsOn = alarms.check_alarm(growssTemp, alarms.hiTempAlarmThreashold, alarms.lowTempAlarmThreashold);
  if(enable_features.debug) {
    Serial.println("------ TEMP ALARM VALUES ------ ");
    Serial.print("hiTempAlarmThreashold is: ");
    Serial.println(alarms.hiTempAlarmThreashold);
    Serial.print("lowTempAlarmThreashold is: ");
    Serial.println(alarms.lowTempAlarmThreashold);
    Serial.print("grows.ino Temp Alarm is on? "); 
    Serial.println(alarms.tempAlarmIsOn);
    Serial.println("grows.ino check_alarm temp is done.\n"); 
  }

  // check humidity alarm
  alarms.humidAlarmIsOn = alarms.check_alarm(growssHumidity, alarms.hiHumidityAlarmThreashold, alarms.lowHumidityAlarmThreashold);
  if(enable_features.debug) {
    Serial.println("------ HUMIDITY ALARM VALUES ------ ");
    Serial.print("hiHumidityThreasholdVar is: ");
    Serial.println(alarms.hiHumidityAlarmThreashold);
    Serial.print("lowHumidityThreasholdVar is: ");
    Serial.println(alarms.lowHumidityAlarmThreashold);
    Serial.print("grows.ino Humid Alarm is on? "); 
    Serial.println(alarms.humidAlarmIsOn);
    Serial.println("grows.ino check_alarm humidity is done.\n"); 
  }

  // check moisture status for both soil moisture sensors
  alarms.moist1AlarmStatus = alarms.check_moisture_alarms(growssMoisture1);
  alarms.moist2AlarmStatus = alarms.check_moisture_alarms(growssMoisture2);
  if(enable_features.debug) {
    Serial.println("------ SOIL MOISTURE STATUS ------ ");
    Serial.print("growssMoisture1Var is: ");
    Serial.println(growssMoisture1);
    Serial.print("moist1AlarmStatus is: ");
    Serial.println(alarms.moist1AlarmStatus);
    Serial.print("growssMoisture2Var is: ");
    Serial.println(growssMoisture2);
    Serial.print("moist2AlarmStatus is: ");
    Serial.println(alarms.moist2AlarmStatus);
    Serial.print("grows.ino check_alarm soil moisture is done.\n"); 
  }

/****************************************************************************/
  // control the hardware
  // control the light
  light.lightIsOn = light.light_cntrl(growss_time.hour, light.lightOnHour, light.lightOffHour);
  if(enable_features.debug) {
    Serial.println("------ LIGHT CONTROL ------ ");
    Serial.print("the current time (hour): ");
    Serial.println(growss_time.hour);
    Serial.print("when light is on: ");
    Serial.println(light.lightOnHour);
    Serial.print("when light is off: ");
    Serial.println(light.lightOffHour);
    Serial.print("growss.ino light on? ");
    Serial.println(light.lightIsOn);
  }

  // Set fan on temp for either day (lights on) or nite (lights off)
  float tempSetpointVar = exhaust_fan.tempSetpoint;
  if (light.lightIsOn) {
      exhaust_fan.tempSetpoint = exhaust_fan.dayTemp;
  }
  else {
      exhaust_fan.tempSetpoint = exhaust_fan.niteTemp;
  }

  // control the exhaust fan
  exhaust_fan.exFanIsOn = exhaust_fan.exhaust_fan_cntrl(growssTemp, growssHumidity, exhaust_fan.tempSetpoint, exhaust_fan.tempHysteresis, exhaust_fan.humidSetpoint, exhaust_fan.humidHysteresis);
  if(enable_features.debug) {
    Serial.println("------ EXHAUST FAN CONTROL ------ ");
     Serial.print("BME temp is: "); 
     Serial.println(growssTemp);
     Serial.print("Exhaust fan temp setpoint is: "); 
     Serial.println(exhaust_fan.tempSetpoint);
     Serial.print("Exhaust fan temp hysteresis is: "); 
     Serial.println(exhaust_fan.tempHysteresis);
     Serial.print("BME humidity is: "); 
     Serial.println(growssHumidity);
     Serial.print("Exhaust fan humidity setpoint is: "); 
     Serial.println(exhaust_fan.humidSetpoint);
     Serial.print("Exhaust fan humidity hysteresis is: "); 
     Serial.println(exhaust_fan.humidHysteresis);
     Serial.print("Exhaust fan on: "); 
     Serial.println(exhaust_fan.exFanIsOn);
     Serial.println("exhaust_fan function done.");
  }

  // control the humidifier
  humidity_cntrl.humidifierIsOn = humidity_cntrl.humid_cntrl( growssHumidity, humidity_cntrl.humiditySetpoint, humidity_cntrl.humidityHysteresis);  
  if(enable_features.debug) {
    Serial.println("------ HUMIDIFIER CONTROL ------ ");
    Serial.print("BME humidity is: "); 
    Serial.println(growssHumidity);
    Serial.print("humiditySetpointVar is: "); 
    Serial.println(humidity_cntrl.humiditySetpoint);
    Serial.print("humidityHisteresisVar is: "); 
    Serial.println( humidity_cntrl.humidityHysteresis);
    Serial.print("humidifier is on? "); 
    Serial.println(humidity_cntrl.humidifierIsOn);
  }

/****************************************************************************/
  // set blynk mobile app led & widget colors
  // set temp & humidity blynk led colors
  blynkLeds.tempBlynkLedColor = blynkLeds.set_blynk_alarm_led_color(alarms.tempAlarmIsOn);
  blynkLeds.humidBlynkLedColor = blynkLeds.set_blynk_alarm_led_color(alarms.humidAlarmIsOn);
  if(enable_features.debug) {
    Serial.println("------ BLYNK TEMP LED COLOR ------ ");
    Serial.print("tempBlynkLedColor is: ");
    Serial.println(blynkLeds.tempBlynkLedColor);
    Serial.print("humidBlynkLedColor is: ");
    Serial.println(blynkLeds.humidBlynkLedColor);
  }

  // set soil moisture leds color on blynk app
  blynkLeds.moist1BlynkLedColor = blynkLeds.set_blynk_moist_alarm_led_color(alarms.moist1AlarmStatus);
  blynkLeds.moist2BlynkLedColor = blynkLeds.set_blynk_moist_alarm_led_color(alarms.moist2AlarmStatus);
  if(enable_features.debug) {
    Serial.println("------ BLYNK SOIL MOISTURE LED COLOR ------ ");
    Serial.print("moist1BlynkLedColor");
    Serial.println(blynkLeds.moist1BlynkLedColor);
    Serial.print("moist2BlynkLedColor");
    Serial.println(blynkLeds.moist2BlynkLedColor);
  }

  // set blynk app led color if on/off
  blynkLeds.exfanBlynkLedColor = blynkLeds.set_blynk_on_led_color(alarms.exhaustFanIsOn);
  blynkLeds.lightBlynkLedColor = blynkLeds.set_blynk_on_led_color(alarms.lightIsOn);
  blynkLeds.humidCntrlLedColor = blynkLeds.set_blynk_on_led_color(alarms.humidifierIsOn);

  
  Serial.println("growss.ino done\n");
  delay(20000);                       // wait for a second
}
