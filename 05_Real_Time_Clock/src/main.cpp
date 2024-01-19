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
#include <RTClib.h>


DateTimeManager dtm;
Afficheur *afficheur; // Un afficheur Oled


const char *ssid = "PA_philippe";
const char *password = "ygyc3556";

void setup() {

    Serial.begin(115200);
    afficheur = new Afficheur;

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        afficheur->afficher('.');
    }
    Serial.print("Connecté au réseau WiFi : ");
    Serial.println(ssid);

    if (dtm.synchro_RTC_Interne(DateTimeManager::RTC_EXTERNE)) {
        Serial.println("La mise à jour de la date et de l'heure a réussi dans rtc interne");
        
        /**Mise à l'heure du RTC externe DS3231 à partir de la rtc interne
        if (dtm.set_RTC_Externe()) {
            Serial.println("La mise à jour de la date et de l'heure a réussi dans rtc externe");
        }
        **/
        
    }
}

void loop() {

    // time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 UTC
    time_t now;

    // renvoie l'heure actuelle du système sous forme de temps depuis l'époque
    time(&now);

    dtm.printDateTime(now);
    afficheur->afficherDateTime(now);


    delay(1000);
    // dtm.synchro_RTC_Interne(DateTimeManager::RTC_EXTERNE);
}

