/* 
 * File:   main.cpp
 * Author: philippe SIMIER Lycée Touchard
 *
 * Created on 18 janv 2024, 12:24
 * 
 * Programme pour configurer l'heure du RTC interne 
 * à partir des serveurs NTP accessibles sur internet
 * puis configuration du RTC externe DS3231
 * 
 * 
 */

#include <Arduino.h>
#include <WiFi.h>
#include <DateTimeManager.h>
#include <Afficheur.h>



DateTimeManager dtm;
Afficheur afficheur; // Un afficheur Oled


const char *ssid = "PA_philippe";
const char *password = "ygyc3556";

void setup() {

    Serial.begin(115200);
    afficheur.init();

    WiFi.begin(ssid, password);
    int n = 0;
    while (WiFi.status() != WL_CONNECTED && n < 20) {
        delay(500);
        Serial.print(".");
        afficheur.afficher('.');
        n++;
    }

    if (dtm.synchro_RTC_Interne(DateTimeManager::NTP)) {
        Serial.println("La mise à jour de la date et de l'heure a réussi dans rtc interne");

        if (dtm.set_RTC_Externe()) {
            Serial.println("La mise à jour de la date et de l'heure a réussi dans rtc externe");
        }
    }
}

void loop() {

    dtm.printCurrentTime();
    afficheur.afficherCurrentTime();
    delay(1000);
}

