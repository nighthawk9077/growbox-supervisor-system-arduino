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

/*
 *************************************************************
  Blynk Timer usage information:
  BlynkTimer provides SimpleTimer functionality:
    http://playground.arduino.cc/Code/SimpleTimer

  Understanding Scope in functions:
  https://forum.arduino.cc/index.php?topic=383064.0

  Debugging Using Serial.print:
  https://www.electrosoftcloud.com/en/debug-with-serial-print/

  Assigning IP addresses, etc for Ethernet Shields:
  https://giovanniorgantini.wordpress.com/2015/03/02/using-the-arduino-ethernet-shield/
 *************************************************************
*/

// arduino libraries
#include <Arduino.h>
#include <Ethernet.h>

// my libraries
#include "growss.h"
#include "hi_low_values.h"
#include "check_alarms.h"
#include "control.h"
#include "growss_blynk.h"
#include "growss_setup.h"

// sensor libraries
#include "Seeed_BME280.h"
#include <Wire.h>
#include "PCF85063TP.h"

//blynk libraries
#include <SPI.h>
#include <BlynkSimpleEthernet.h>

PCD85063TP RTclock;// instantiate clock object
BME280 bme280;  // instantiate bme280 object

// Define Structures
Growss_time growss_time; 
Enable_features enable_features; // flags to enable features 
Growss_data growss_data;
// float growssTemp;   // temperature read from the bme280
// float growssHumidity;    // humidity read from the bme280
// float growssPressure;    // presser read from bme280
// int growssMoisture1;    // soil moisture #1 is read
// int growssMoisture2;    // soil moisure #2 is read
Hi_lows hi_lows;  // the high & low values of the day
Alarms alarms;  // what alarms are there?
Light light;  // led light settings
Exhaust_fan exhaust_fan;  // the exhuast fan variables
Humid_Cntrl humidity_cntrl;  // control the humidifier/dehumidifier
BlynkLeds blynkLeds; // the color of the blynk mobil app leds & widgets

BlynkTimer timer;

/****************************************************************************/
// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(115200);
    setup_atmega2560(); // initialize ATMEGA Pins

    // initialize bme280
    if(!bme280.init()){
      Serial.println("Device error!");
    }

    // growss_welcome();
    enable_features.debug = 1; //turn on debugging
    growss_time.setTime = 0;  // set the time if the flag is 1
    growss_data.humidity = 10.0;
    growss_data.moisture1 = 100;
    growss_data.moisture2 = 100;
    growss_data.temp = 75.0;

    // light control variables
    light.lightOnHour = 9; // 9am
    light.lightOnMinute = 0;
    light.lightOffHour = 20; // 9pm
    light.lightOffMinute = 0;

    growss_time.sec = 30;

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
    delay(1000);  // delay 1 sec
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
    growss_data.temp = (9/5) * bme280.getTemperature() + 32; //convert to deg f
    growss_data.temp = 1.5107*(growss_data.temp) - 14.541;    // calibrate temp
    growss_data.humidity = bme280.getHumidity();
    growss_data.humidity = (0.8223 * growss_data.humidity + 15.386);  // calibrate humidity
    growss_data.pressure = bme280.getPressure();

    // get current soil moisture values
    growss_data.moisture1 = analogRead(MOISTURE1);
    growss_data.moisture2 = analogRead(MOISTURE2);

    // set the current values as the baseline hi & low values
    hi_lows.hiTemp = growss_data.temp;
    hi_lows.lowTemp = growss_data.temp;
    hi_lows.hiHumidity = growss_data.humidity;
    hi_lows.lowHumidity = growss_data.humidity;
    hi_lows.hiPressure = growss_data.pressure;
    hi_lows.lowPressure = growss_data.pressure;
    // moisture values
    hi_lows.hiMoisture1 = growss_data.moisture1;
    hi_lows.lowMoisture1 = growss_data.moisture1;
    hi_lows.hiMoisture2 = growss_data.moisture2;
    hi_lows.lowMoisture2 = growss_data.moisture2;

    Serial.print("setup funct baseline growss_data.temp is: "); 
    Serial.println(growss_data.temp);
    Serial.print("setup funct baseline hi temp is: "); 
    Serial.println(hi_lows.hiTemp);
    Serial.print("setup funct baseline low temp is: "); 
    Serial.println(hi_lows.lowTemp);
    Serial.println("setup funct temp hi_lows debug done.");
    Serial.println("setup funct done\n");

    Blynk.begin(BLYNK_AUTH);
    // You can also specify server:
    // Blynk.begin(auth, "blynk-cloud.com", 80);
    // Blynk.begin(BLYNK_AUTH, IPAddress(192,168,1,100), 8080);
    // For more options, see Boards_Ethernet/Arduino_Ethernet_Manual example

    // Setup functions to be called every 2 seconds
    timer.setInterval(2000L, write_values_to_blynk);  
    timer.setInterval(2000L, write_hi_lows_to_blynk);
    timer.setInterval(2000L, write_alarms_to_blynk);
    timer.setInterval(2000L, write_setpoints_to_blynk);
    timer.setInterval(2000L, write_leds_to_blynk);
    timer.setInterval(2000L, write_version_to_blynk);
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
  growss_data.temp = (9/5) * bme280.getTemperature() + 32; //convert to deg f
  growss_data.temp = 1.5107*(growss_data.temp) - 14.541;    // calibrate temp
  growss_data.humidity = bme280.getHumidity();
  growss_data.humidity = (0.8223 * growss_data.humidity + 15.386);  // calibrate humidity

  growss_data.pressure = bme280.getPressure() * 0.00029530;
  if (enable_features.debug) {
    Serial.println("------ BME280 VALUES ------ ");
    Serial.print("growss.ino cur temp value is: ");
    Serial.println(growss_data.temp);
    Serial.print("growss.ino cur humid value is: ");
    Serial.println(growss_data.humidity);
    Serial.print("growss.ino cur pressure value is: ");
    Serial.println(growss_data.pressure);
  }

  // get current soil moisture values
  growss_data.moisture1 = analogRead(MOISTURE1);
  growss_data.moisture2 = analogRead(MOISTURE2);
  if( enable_features.debug) {
    Serial.println("------ MOISTURE VALUES ------ ");
    Serial.print("growss.ino moisture1 value: ");
    Serial.println(growss_data.moisture1);
    Serial.print("growss.ino moisture2 value: ");
    Serial.println(growss_data.moisture2);
  }
  delay(3000);

/****************************************************************************/
  // get hi & low temp values
  hi_lows.hiTemp = hi_lows.setHiValue(growss_data.temp, hi_lows.hiTemp);
  hi_lows.lowTemp = hi_lows.setLowValue(growss_data.temp,  hi_lows.lowTemp);

  // get hi & low humidity values
  hi_lows.hiHumidity = hi_lows.setHiValue(growss_data.humidity, hi_lows.hiHumidity);
  hi_lows.lowHumidity = hi_lows.setLowValue(growss_data.humidity, hi_lows.lowHumidity);

  // get hi & low pressure values
  hi_lows.hiPressure = hi_lows.setHiValue(growss_data.pressure, hi_lows.hiPressure);
  hi_lows.lowPressure = hi_lows.setLowValue(growss_data.pressure, hi_lows.lowPressure);

  // get hi & low soil moisture #1 values
  hi_lows.hiMoisture1 = hi_lows.setHiMoisture(growss_data.moisture1, hi_lows.hiMoisture1);
  hi_lows.lowMoisture1 = hi_lows.setLowMoisture(growss_data.moisture1, hi_lows.lowMoisture1);

  // get hi & low soil moisture #2 values
  hi_lows.hiMoisture2 = hi_lows.setHiMoisture(growss_data.moisture2, hi_lows.hiMoisture2);
  hi_lows.lowMoisture2 = hi_lows.setLowMoisture(growss_data.moisture2, hi_lows.lowMoisture2);
  if(enable_features.debug) {
    Serial.println("------ HI/LOW VALUES ------ ");
    Serial.print("growss.ino growss_data.temp is: ");
    Serial.println(growss_data.temp);
    Serial.print("growss.ino hi temp is: ");
    Serial.println(hi_lows.hiTemp);
    Serial.print("growss.ino low temp is: ");
    Serial.println(hi_lows.lowTemp);
  }

/****************************************************************************/
  // check for alarms
  // check temp alarm
  alarms.tempAlarmIsOn = alarms.check_alarm(growss_data.temp, alarms.hiTempAlarmThreashold, alarms.lowTempAlarmThreashold);
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
  alarms.humidAlarmIsOn = alarms.check_alarm(growss_data.humidity, alarms.hiHumidityAlarmThreashold, alarms.lowHumidityAlarmThreashold);
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
  alarms.moist1AlarmStatus = alarms.check_moisture_alarms(growss_data.moisture1);
  alarms.moist2AlarmStatus = alarms.check_moisture_alarms(growss_data.moisture2);
  if(enable_features.debug) {
    Serial.println("------ SOIL MOISTURE STATUS ------ ");
    Serial.print("growss_data.moisture1Var is: ");
    Serial.println(growss_data.moisture1);
    Serial.print("moist1AlarmStatus is: ");
    Serial.println(alarms.moist1AlarmStatus);
    Serial.print("growss_data.moisture2Var is: ");
    Serial.println(growss_data.moisture2);
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
  exhaust_fan.exFanIsOn = exhaust_fan.exhaust_fan_cntrl(growss_data.temp, growss_data.humidity, exhaust_fan.tempSetpoint, exhaust_fan.tempHysteresis, exhaust_fan.humidSetpoint, exhaust_fan.humidHysteresis);
  if(enable_features.debug) {
    Serial.println("------ EXHAUST FAN CONTROL ------ ");
     Serial.print("BME temp is: "); 
     Serial.println(growss_data.temp);
     Serial.print("Exhaust fan temp setpoint is: "); 
     Serial.println(exhaust_fan.tempSetpoint);
     Serial.print("Exhaust fan temp hysteresis is: "); 
     Serial.println(exhaust_fan.tempHysteresis);
     Serial.print("BME humidity is: "); 
     Serial.println(growss_data.humidity);
     Serial.print("Exhaust fan humidity setpoint is: "); 
     Serial.println(exhaust_fan.humidSetpoint);
     Serial.print("Exhaust fan humidity hysteresis is: "); 
     Serial.println(exhaust_fan.humidHysteresis);
     Serial.print("Exhaust fan on: "); 
     Serial.println(exhaust_fan.exFanIsOn);
     Serial.println("exhaust_fan function done.");
  }

  // control the humidifier
  humidity_cntrl.humidifierIsOn = humidity_cntrl.humid_cntrl( growss_data.humidity, humidity_cntrl.humiditySetpoint, humidity_cntrl.humidityHysteresis);  
  if(enable_features.debug) {
    Serial.println("------ HUMIDIFIER CONTROL ------ ");
    Serial.print("BME humidity is: "); 
    Serial.println(growss_data.humidity);
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

  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  
  Serial.println("growss.ino done\n");
  delay(20000);                       // wait for a second
}

/****************************************************************************/
// Blynk Functions
/****************************************************************************/
// sends the GROWSS version info to the Blynk app
void write_version_to_blynk()
{
    Blynk.setProperty(BLYNK_GROWSS_NAME, "label", "NAME:");
    Blynk.virtualWrite(BLYNK_GROWSS_NAME, GROWSS_NAME1);
    Blynk.setProperty(BLYNK_GROWSS_VERSION, "label", "VERSION:");
    Blynk.virtualWrite(BLYNK_GROWSS_VERSION, GROWSS_VER);
    Blynk.setProperty(BLYNK_GROWSS_AUTH, "label", "AUTHOR:");
    Blynk.virtualWrite(BLYNK_GROWSS_AUTH, GROWSS_AUTH);
    Blynk.setProperty(BLYNK_GROWSS_LIC, "label", "COPYWRITE LIC:");
    Blynk.virtualWrite(BLYNK_GROWSS_LIC, GROWSS_LIC);
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second
}

// sends the most recent widget colores for the is on/off? leds to the Blynk app
void write_leds_to_blynk()
{
    // exhaust fan led
    Blynk.setProperty(BLYNK_EX_FAN_LED, "label", "FAN");
    Blynk.setProperty(BLYNK_EX_FAN_LED, "color", blynkLeds.exfanBlynkLedColor);
    Blynk.virtualWrite(BLYNK_EX_FAN_LED, '255'); // turn led on

    // grow light led
    Blynk.setProperty(BLYNK_LIGHT_LED, "label", "LIGHT");
    Blynk.setProperty(BLYNK_LIGHT_LED, "color", blynkLeds.lightBlynkLedColor); // light LED on gui
    Blynk.virtualWrite(BLYNK_LIGHT_LED, '255');

    // humidifier led
    Blynk.setProperty(BLYNK_HUMIDIFIER_LED, "label", "HUMID");
    Blynk.setProperty(BLYNK_HUMIDIFIER_LED, "color", blynkLeds.humidCntrlLedColor); // light LED on gui
    Blynk.virtualWrite(BLYNK_HUMIDIFIER_LED, '255');
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second
}

// sends the most recent setpoin values (to control fan, humidifier) to the Blynk app
void write_setpoints_to_blynk()
{
    Blynk.setProperty(BLYNK_FAN_TEMP_SETPNT, "color", BLYNK_STEEL_BLUE); // steel blue
    Blynk.setProperty(BLYNK_FAN_TEMP_SETPNT, "label", "FAN ON TEMP");
    Blynk.virtualWrite(BLYNK_FAN_TEMP_SETPNT, String(exhaust_fan.tempSetpoint)); // temp (+/- hysteresis) when fan turns on
    Blynk.setProperty(BLYNK_FAN_HUMID_SETPOINT, "color", BLYNK_STEEL_BLUE); // steel blue
    Blynk.setProperty(BLYNK_FAN_HUMID_SETPOINT, "label", "FAN ON HUMID:");
    Blynk.virtualWrite(BLYNK_FAN_HUMID_SETPOINT, String(exhaust_fan.humidSetpoint)); // humidity (+/- hysteresis) when fan turns on
    Blynk.setProperty(BLYNK_FAN_TEMP_HYSTERESIS, "color", BLYNK_CORN_BLUE); // corn flower blue
    Blynk.setProperty(BLYNK_FAN_TEMP_HYSTERESIS, "label", "TEMP HYSTERESIS:");
    Blynk.virtualWrite(BLYNK_FAN_TEMP_HYSTERESIS, String(exhaust_fan.tempHysteresis)); // temp hysteresis
    delay(1000);  // blyk says to only allow up to 10 values send to app in a second
    
    Blynk.setProperty(BLYNK_FAN_HUMED_HYSTERESIS, "color", BLYNK_GREEN); // green
    Blynk.setProperty(BLYNK_FAN_HUMED_HYSTERESIS, "label", "HUMID HYSTERESIS:");
    Blynk.virtualWrite(BLYNK_FAN_HUMED_HYSTERESIS, String(exhaust_fan.humidHysteresis)); // humidity hysteresis

    Blynk.setProperty(BLYNK_LIGHT_ON_TIME, "color", BLYNK_GOLD); // gold
    Blynk.setProperty(BLYNK_LIGHT_ON_TIME, "label", "LIGHTS ON TIME:");
    Blynk.virtualWrite(BLYNK_LIGHT_ON_TIME, String(light.lightOnHour)); // when lights turns on
    Blynk.setProperty(BLYNK_LIGHT_OFF_TIME, "color", BLYNK_GOLD); // gold
    Blynk.setProperty(BLYNK_LIGHT_OFF_TIME, "label", "LIGHTS OFF TIME:");
    Blynk.virtualWrite(BLYNK_LIGHT_OFF_TIME, String(light.lightOffHour)); // when lights turns off
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second
}

// sends the most recent alarm values to the Blynk app
void write_alarms_to_blynk()
{
    // check for alarms
    Blynk.setProperty(BLYNK_TEMP, "color", blynkLeds.tempBlynkLedColor);
    Blynk.setProperty(BLYNK_HI_TEMP_ALARM_VALUE, "label", "HI ALARM TEMP");
    Blynk.virtualWrite(BLYNK_HI_TEMP_ALARM_VALUE, String(alarms.hiTempAlarmThreashold));
    Blynk.setProperty(BLYNK_LO_TEMP_ALARM_VALUE, "label", "LO ALARM TEMP");
    Blynk.virtualWrite(BLYNK_LO_TEMP_ALARM_VALUE, String(alarms.lowTempAlarmThreashold));

    Blynk.setProperty(BLYNK_HUMID, "color", blynkLeds.humidBlynkLedColor);
    Blynk.setProperty(BLYNK_HI_HUMID_ALARM_VALUE, "label", "HI ALARM HUMID");
    Blynk.virtualWrite(BLYNK_HI_HUMID_ALARM_VALUE, String(alarms.hiHumidityAlarmThreashold));
    Blynk.setProperty(BLYNK_LO_HUMID_ALARM_VALUE, "label", "LO ALARM HUMID");
    Blynk.virtualWrite(BLYNK_LO_HUMID_ALARM_VALUE, String(alarms.lowHumidityAlarmThreashold));
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second

    Blynk.setProperty(BLYNK_MOIST1_ALARM, "color", blynkLeds.moist1BlynkLedColor);
    Blynk.setProperty(BLYNK_MOIST1_ALARM, "label", "SOIL#1 IS ");
    Blynk.virtualWrite(BLYNK_MOIST1_ALARM, String(alarms.moist1AlarmStatus));

    Blynk.setProperty(BLYNK_MOIST2_ALARM, "color", blynkLeds.moist2BlynkLedColor);
    Blynk.setProperty(BLYNK_MOIST2_ALARM, "label", "SOIL#2 IS ");
    Blynk.virtualWrite(BLYNK_MOIST2_ALARM, String(alarms.moist2AlarmStatus));
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second

    Blynk.setProperty(BLYNK_HI_DENSITY_ALARM, "color", blynkLeds.densityBlynkLedColor);
    Blynk.setProperty(BLYNK_HI_DENSITY_ALARM, "label", "HI ALARM DENSITY");
    Blynk.virtualWrite(BLYNK_HI_DENSITY_ALARM, String(alarms.hiDensityAlarmThreashold));

    // // smoke LED
    Blynk.setProperty(BLYNK_HI_DENSITY_LED, "label", "SMOKE!");
    Blynk.setProperty(BLYNK_HI_DENSITY_LED, "color", blynkLeds.densityBlynkLedColor); // smoke LED on gui
    Blynk.virtualWrite(BLYNK_HI_DENSITY_LED, '255');
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second
}

// sends the most recent hi & low values to the Blynk app
void write_hi_lows_to_blynk()
{
    // high & low values
    Blynk.setProperty(BLYNK_HI_TEMP_VALUE, "label", "HI TEMP TODAY");
    Blynk.virtualWrite(BLYNK_HI_TEMP_VALUE, String(hi_lows.hiTemp));
    Blynk.setProperty(BLYNK_LO_TEMP_VALUE, "label", "LO TEMP TODAY");
    Blynk.virtualWrite(BLYNK_LO_TEMP_VALUE, String(hi_lows.lowTemp));

    Blynk.setProperty(BLYNK_HI_HUMID_VALUE, "label", "HI HUMID TODAY");
    Blynk.virtualWrite(BLYNK_HI_HUMID_VALUE, String(hi_lows.hiHumidity));
    Blynk.setProperty(BLYNK_LO_HUNMID_VALUE, "label", "LO HUMID TODAY");
    Blynk.virtualWrite(BLYNK_LO_HUNMID_VALUE, String(hi_lows.lowHumidity));
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second

    Blynk.setProperty(BLYNK_HI_MOIST1_VALUE, "label", "HI MOISTURE1 TODAY");
    Blynk.virtualWrite(BLYNK_HI_MOIST1_VALUE, String(hi_lows.hiMoisture1));
    Blynk.setProperty(BLYNK_LO_MOIST1_VALUE, "label", "LO MOISTURE1 TODAY");
    Blynk.virtualWrite(BLYNK_LO_MOIST1_VALUE, String(hi_lows.hiMoisture1));

    Blynk.setProperty(BLYNK_HI_MOIST2_VALUE, "label", "HI MOISTURE2 TODAY");
    Blynk.virtualWrite(BLYNK_HI_MOIST2_VALUE, String(hi_lows.hiMoisture2));
    Blynk.setProperty(BLYNK_LO_MOIST2_VALUE, "label", "LO MOISTURE2 TODAY");
    Blynk.virtualWrite(BLYNK_LO_MOIST2_VALUE, String(hi_lows.lowMoisture2));
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second
}

// sends the most recent measured values to the Blynk app
void write_values_to_blynk()
{
    // concatenate date & time for the Blynk app
    growss_time.date = (String(growss_time.year) + "-" + String(growss_time.month) + "-" + String(growss_time.dayOfMonth));
    growss_time.time = (String(growss_time.hour) + ":" + String(growss_time.min) + ":" + String(growss_time.sec));
    growss_time.dateTime = growss_time.dateTime + growss_time.time;

    // send software info to blynk
    Blynk.setProperty(BLYNK_TIME, "color", BLYNK_GREEN);
    Blynk.virtualWrite(BLYNK_TIME, growss_time.dateTime); // converted to string already

    Blynk.setProperty(BLYNK_TEMP, "label", "CURRENT TEMP");
    Blynk.virtualWrite(BLYNK_TEMP, String(growss_data.temp));
    Blynk.setProperty(BLYNK_HUMID, "label", "CURRENT HUMIDITY");
    Blynk.virtualWrite(BLYNK_HUMID, String(growss_data.humidity));

    Blynk.setProperty(BLYNK_MOISTURE1, "label", "CURRENT MOISTURE1");
    Blynk.virtualWrite(BLYNK_MOISTURE1, String(growss_data.moisture1));

    Blynk.setProperty(BLYNK_MOISTURE2, "label", "CURRENT MOISTURE2");
    Blynk.virtualWrite(BLYNK_MOISTURE2, String(growss_data.moisture2));
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second

    Blynk.setProperty(BLYNK_PRESS, "label", "CURRENT PRESSURE");
    Blynk.virtualWrite(BLYNK_PRESS, String(growss_data.pressure));
    delay(1000);  // blynk says to only allow up to 10 values send to app in a second
}

