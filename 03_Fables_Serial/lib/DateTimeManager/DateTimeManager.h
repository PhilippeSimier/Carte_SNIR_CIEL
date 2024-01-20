/* 
 * File:   DateTimeManager.h
 * Author: Philippe SIMIER Lycée Touchard le Mans
 *
 * Created on 11 janvier 2024, 17:40
 */

#ifndef DATETIMEMANAGER_H
#define DATETIMEMANAGER_H

#include <Arduino.h>
#include <RTClib.h>
#include <WiFi.h>

class DateTimeManager {

public:
    
    enum MODE_SYNCHRO {
        NTP,
        RTC_EXTERNE,
        AUTO,
    };

    DateTimeManager();
    virtual ~DateTimeManager();

    int setCurrentTime(unsigned long epoch);
    unsigned long getCurrentTime() const;
    void printDateTime(const time_t _time, Stream &flux = Serial) const;
    bool synchro_RTC_Interne(MODE_SYNCHRO mode = AUTO);
    bool set_RTC_Externe();

private:

    String ntpServerName[3];
    String timeZone;
    RTC_DS3231 *rtc_externe;

};

#endif /* DATETIMEMANAGER_H */

