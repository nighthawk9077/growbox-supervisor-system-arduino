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

#ifndef _GET_HI_LOW_VALUES_H_
#define _GET_HI_LOW_VALUES_H_

class Hi_lows {
    public:
        float hiTemp;
        float lowTemp;
        float hiHumidity;
        float lowHumidity;
        float hiPressure;
        float lowPressure;

        int hiMoisture1;
        int lowMoisture1;
        int hiMoisture2;
        int lowMoisture2;

        // methods
        float setHiValue(float, float);
        float setLowValue(float, float);

        int setHiMoisture(int, int);
        int setLowMoisture(int, int);
};
#endif