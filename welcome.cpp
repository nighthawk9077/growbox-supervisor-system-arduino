/*
########
# Version: V19-05-20-V1B (This is a working BETA vesion)
    Nighthawk
    4.20.20
    Version: V20-20-04
    
    This project is released under The MIT License (MIT)
    Copyright 2020 Nighthawk
########

########
# startup splash screen with Version information
########
*/
#include <Arduino.h>
#include "growss.h"

void growss_welcome() {
    // print cool splash screen to stdio
    // Serial.println("\n\n\n\n\n\n\n\n\n");
    // Serial.println(" #####   ######   #######  #       #   #####    ##### "); 
    // Serial.println("#     #  #     #  #     #  #   #   #  #     #  #     #"); 
    // Serial.println("#        #     #  #     #  #   #   #  #        #      "); 
    // Serial.println("#  ####  ######   #     #  #   #   #   #####    ##### "); 
    // Serial.println("#     #  #   #    #     #  #   #   #        #        #"); 
    // Serial.println("#     #  #    #   #     #  #   #   #  #     #  #     #"); 
    // Serial.println(" #####   #     #  #######   ### ###    #####    ##### "); 
    // delay(100);
    // Serial.println("\n");
    Serial.println("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ$:$ZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ:D?ZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ,8~OZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZ:88,$ZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZOOZZZZZZZZZZZZZZZZZZO?ND8$:ZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZOZZ+:OZZZZZZZZZZZZZZZO7:NDDD:$ZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZ:8~OOZZZZZZZZZZZZZO=:DDD8??ZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZOZZ~8D:ZZZZZZZZZZZZZZO,DDDDDD:ZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZ+ID8,:OZZZZZZZZZZZ?8DDDDD8:OZZZZZZZZZZZZZO$:7ZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZ,888O~IZZZZZZZZZZ=,DDDDDN+$ZZZZZZZZZZOO~:8~$ZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZOZ:O8888,:$OZZZZZZZ+ODDDDD8:ZZZZZZZZZZ$:88DO?ZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZ~I88888N:IZZZZZZZ:DDDDD8D:ZZOZZZZZI:D8DDD,OZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZ$~D8DDD88,=ZZZZZZ:ODDDDDD?7ZZZZZ7,O888D8,=OOZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZO?=DDDDD8D,IZZZZZ:DDDDDDD?~ZZZZ::DDDDDD,=ZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZZI:DDDDDDD:ZOZZZ~DDDDDDD~IZO7:IDDDD88::OZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZO$:O8DDDDDDD~ZOO,DDDDDDD,ZO~,DDDDDD8=:OOOZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZZZ$,8DDDDDDD::ZZ=ZDD8DDDO7~:NDDDDDD8~OOZZZZZZZZZZZZ");
    delay(100);
    Serial.println("ZZZZZZZZZZZZI8DDDDDDND:~Z+8DD8DDD:+:DDD8DDDN:OZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("Z7IZZZZZ$ZZZZ7~DDDDDDDD:Z:,8D8DDD~~DDD8DDNN:ZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("$:88I8~,:77Z$Z+~DDDDDDDM:=NDDDDD8::DDDDDD:~$ZZZZZZZZZZZZZZZZ");
    delay(100);
    Serial.println("$$:+DD8DDDD,:+ZI~+DDDDDD.:,DDDDDN.NDDDD8:+$Z$$$$$$$$$$$$$$$$");
    delay(100);
    Serial.println("$$$I:8DD8DDDDD,:~:=8DDDDD:~D8DD8:NDDD8D:=$$$$$$$$$Z77$$$$$$$");
    delay(100);
    Serial.println("$$$$$:,DDDDDD8DDDO:ODDDDDD,:N8DD,DDDND,=$$$I=:,,N$D8887$:::$");
    delay(100);
    Serial.println("777777?:88DDDDDDDDD8ND8D8D:ND8DM8DDNN:I=::?DN8DDDDD8888D+:I7");
    delay(100);
    Serial.println("777777777,$DDDDDDDDDN8+O8DD,D8D+D88,~,Z88DDDD8DNDDDD8::~7777");
    delay(100);
    Serial.println("77777777777:,:DDDDDDD8DN.D8:78?78,::DDDN8DNDDND88D,,?I777777");
    delay(100);
    Serial.println("IIIIIIIIIIIII?=:~Z8DNDD8DM$8,8:8::M8DDN8DDDD8N,,:?IIIIIIIIII");
    delay(100);
    Serial.println("IIIIIIIIIIIIIII=:,:,~=,DNDDOD88?8DDDDND,=?::=I?IIIIIIIIIIIII");
    delay(100);
    Serial.println("IIIIIIIIIIII+:?8DDD8DDDDDD8DDD88888DNDM:,,=?IIIIIIIIIIIIIIII");
    delay(100);
    Serial.println("IIIIIII??I~:8DDD8DNNDDDD=,$N8$,DZDNND88DDDNZ,:?I?IIIIIIIIIII");
    delay(100);
    Serial.println("???????I+~N8DDDD8DN8,::,$DDD:8~+DDMZDNDDDDDDDD~:+?I?????????");
    delay(100);
    Serial.println("??????+,NNOD7,,,:~??=:MNDDD,:$+~:NNDM,?NDDDDNNNN8:??????????");
    delay(100);
    Serial.println("???????+???????????~?DNND,:?~O=??:,DDD:=:~:N$DNDD8,+????????");
    delay(100);
    Serial.println("??????????????????+,DI::??????????++:DI=?????++~::,+:???????");
    delay(100);
    Serial.println("???????????????????~?????????????????:?:????????????????????");
    delay(100);
    Serial.println("??????????????????????????????????????~=????????????????????");
    delay(100);
    Serial.println("????????????????????????????????????????????????????????????");
    delay(100);
    Serial.println("");
    delay(100);

    // Serial.println("#######                   #####  ######  ####### #     #");                         
    // Serial.println("   #    #    # ######    #     # #     # #     # #  #  # #####   ####  #    #"); 
    // Serial.println("   #    #    # #         #       #     # #     # #  #  # #    # #    #  #  #"); 
    // Serial.println("   #    ###### #####     #  #### ######  #     # #  #  # #####  #    #   ##");       
    // Serial.println("   #    #    # #         #     # #   #   #     # #  #  # #    # #    #   ##");       
    // Serial.println("   #    #    # #         #     # #    #  #     # #  #  # #    # #    #  #  #");      
    // Serial.println("   #    #    # ######     #####  #     # #######  ## ##  #####   ####  #    #");     
    // Serial.println("");
    // Serial.println(" #####                                                                #####");                                      
    // Serial.println("#     # #    # #####  ###### #####  #    # #  ####   ####  #####     #     # #   #  ####  ##### ###### #    #");     
    // Serial.println("#       #    # #    # #      #    # #    # # #      #    # #    #    #        # #  #        #   #      ##  ##");     
    // Serial.println(" #####  #    # #    # #####  #    # #    # #  ####  #    # #    #     #####    #    ####    #   #####  # ## #");     
    // Serial.println("      # #    # #####  #      #####  #    # #      # #    # #####           #   #        #   #   #      #    #");     
    // Serial.println("#     # #    # #      #      #   #   #  #  # #    # #    # #   #     #     #   #   #    #   #   #      #    #");     
    // Serial.println(" #####   ####  #      ###### #    #   ##   #  ####   ####  #    #     #####    #    ####    #   ###### #    #");     

    delay(100);
    Serial.println("");
    Serial.println(GROWSS_NAME1);
    Serial.print("GROWSS Author: ");
    Serial.println(GROWSS_NAME2);
    Serial.print("GROWSS Author: ");
    Serial.println(GROWSS_AUTH);
    Serial.print("VERSION: ");
    Serial.println(GROWSS_VER);
    Serial.print("GROWSS LICENSE: ");
    Serial.println(GROWSS_LIC);
    Serial.print("\n\n\n");

/****************************************************************/
    // turn off/on exhaust fan (exhaust fan is already on by default)
    Serial.println("FAN OFF/ON");
    digitalWrite(EXHAUST_FAN, 1);     // turn off exhaust fan        
    delay(1000);
    digitalWrite(EXHAUST_FAN, 0);     // turn on exhaust fan        
	
    // turn on/off buzzer
    Serial.println("BUZZER ON/OFF");
    digitalWrite(BUZZER, 1);     // turn on buzzer
    delay(500);
    digitalWrite(BUZZER, 0);     // turn off buzzer
}
