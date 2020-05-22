# growbox-supervisor-system-arduino
# The GROWbox Supervisor System (GROWSS)

Nighthawk
Copywrite, 2020 MIT License

### Change Log:

    - Date: 20-04-20  Version: V20-04-20-Arduino
        - Original working code.
            - temp, humidity, pressure & soil moisture
            - alarms, hi & lows
            - controlls light, exhaust fan, & humidifier
___________________________________________________________________________________________

### This is my design of a GROWbox Supervisor System (GROWSS) Arduino Version. The GROWSS system monitors temp, humidty, & soil moisture for 2 potted plants inside a grow box or tent. It also controls the lights, exhaust fan, & humidifier.

### A Blynk mobile app is used to monitor the values & alert when thre is an alarm present.

### The GROWSS system will be used in a 2'x2'x6' grow box, but can be used for other sizes of grow box/cabinet/room/tent.

### This design will have many stages until completion.  Check documentation in the 'Files' tab above for detailed descriptions of the design.

### The GROWbox Supervisor System-GROWSS Weppage is here:
#### <https://sites.google.com/view/thegrowsssystem>

### The GROWbox Supervisor System-GROWSS Youtube page is here:
#### <https://www.youtube.com/channel/UCl3MO4rn05THPnm7vnGfwRA/>

### My email:
#### <growbox.supervisor.system.growss@gmail.com>

### The Cannabis Reviewer's Website where you can see the GROWSS in action!
### Follow every week to find out the latest with my cannabis grow here:
##### <https://www.youtube.com/channel/UC_jE8LQd4k3gbLMrVrgcGjg>

### Other relevant links:
#### Arduino: <https://www.arduino.cc/>
#### Grove Sensors: <http://wiki.seeedstudio.com/Grove_System/>
#### Blynk C++ Library: <https://github.com/blynkkk/blynk-library>
#### Blynk Local Server: <https://github.com/blynkkk/blynk-server>

#### Working Design goals are:

- [x] Read Temp (temp/humidity sensor)
- [x] Read Humidity (temp/humidity sensor)
- [x] Read Soil Moisture for 2 plants (soil moisture sensor)
- [ ] Save information to local storage as a tab delimeted text file.
- [x] Increase humidity in grow box if humidity is too low (humidifier)
- [ ] Decrease humidity in grow box if humidity is too high (de-humidifier)
- [ ] IoT/Web page/mobile device access/control
- [ ] Push alarms to me via text/email
- [x] Turn grow lights on/off using RPI (relay)
- [x] Turn on/off fan based on day or nite temp & humidity using RPI (relay)
- [ ] Enable/Disable email, text, fan, light, leds, RGB LCD, & atomizer (humidifier)

#### Icing on the cake would be:

- [ ] Interactive controls for changing env values using blynk app
- [ ] Automatically water plant when soil moisture is too low.
- [ ] Retain values after a crash or reboot.
- [ ] Catch more errors to avoid program crash from broken sensors, etc.
- [ ] Enable/Disable email, text, fan, light, & atomizer (humidifier) from Blynk app.

___________________________________________________________________________________________
 
USING FREE VISUAL STUDIO CODE IDE WITH GITHUB
    <https://code.visualstudio.com//#built-in-git>
    <https://code.visualstudio.com/docs/editor/versioncontrol>
    <https://youtu.be/wMqukSKYcvU>                    - Video showing how to use git in Vstudio Code
___________________________________________________________________________________________
License
This project is released under The MIT License (MIT)

Copyright 2020 Nighthawk

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  
  
  