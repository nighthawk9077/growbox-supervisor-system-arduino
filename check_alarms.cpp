/*
########
    Nighthawk
    4.20.20
    Version: V20-20-04
    
    This project is released under The MIT License (MIT)
    Copyright 2019 Nighthawk
########

########
# checks to see if any alarms are present
########
*/
#include <Arduino.h>
#include "check_alarms.h"

// sets alarm if value is above or below threashold
bool Alarms::check_alarm(float growssValue, float hiValueThreashold, float lowValueThreashold){
    bool AlarmIsOnVar;
    // Check temperature alarms
    if( lowValueThreashold < growssValue && hiValueThreashold > growssValue){
      AlarmIsOnVar = 0; // there isn't an alarm
    }
    else{
      AlarmIsOnVar = 1; // there is an alarm
    }
    Serial.println("------ CHECK ALARMS FUNC ------ ");
    Serial.print("current growss value is: "); 
    Serial.println(growssValue);
    Serial.print("hiValueThreashold is: ");
    Serial.println(hiValueThreashold);
    Serial.print("lowValueThreashold is: ");
    Serial.println(lowValueThreashold);
    Serial.print(" alarm is: "); 
    Serial.println(AlarmIsOnVar);
    Serial.println("check alarm function done .\n");
    return AlarmIsOnVar;
}

/****************************************************************************/
// sets alarm if moisture alarm value is above or below the threashold value
String Alarms::check_moisture_alarms(int growssMoistureValue){
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
    String moistAlarmStatusVar;
    // convert moisture value to human readable text 
    // Soil Moisture Sensor 1
    switch(growssMoistureValue) {
      case 0 ... 17:
        moistAlarmStatusVar = "AIR";
        break;
      case 18 ... 424:
        moistAlarmStatusVar = "DRY";
      case 425 ... 689:
        moistAlarmStatusVar = "PERFECT";
        break;
      default :
        moistAlarmStatusVar = "WATER";
    }  
    return moistAlarmStatusVar;
}
