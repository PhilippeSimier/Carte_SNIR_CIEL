/* 
 * File:   DateTimeManager.cpp
 * Author: Philippe Simier Lycée Touchard Washington Le Mans
 * 
 * Created on 11 janvier 2024, 17:40
 */

#include "DateTimeManager.h"

DateTimeManager::DateTimeManager() {

    ntpServerName[0] = "ntp-p1.obspm.fr";
    ntpServerName[1] = "pool.ntp.org";
    timeZone = "CET-1CEST,M3.5.0,M10.5.0/3";
    rtc_externe = new RTC_DS3231();
}

DateTimeManager::~DateTimeManager() {
    delete rtc_externe;
}

/**
 * @brief   Methode pour synchroniser la RTC avec un serveur de temps
 *          ou une RTC externe DS3231
 *          elle permet aussi de définir une timeZone.
 * @param   MODE_SYNCHRO  NTP ou RTC_EXTERNE
 * @return  true si la synchronisation réussie
 */
bool DateTimeManager::synchro_RTC_Interne(MODE_SYNCHRO mode) {

    struct tm timeinfo;
    struct timeval new_time;
    extern WiFiClass WiFi;

    int retour = 0;
    
    // Si le mode est AUTO avec un rtc externe présent
    if (mode == AUTO && rtc_externe->begin()){
        mode = RTC_EXTERNE;
    }
    // Si le mode AUTO avec une connexion internet est présente
    if (mode == AUTO && WiFi.status() == WL_CONNECTED){
        mode = NTP;
    }


    switch (mode) {
        case NTP: // connexion aux serveurs NTP, avec un offset nul. Temps UTC
            configTime(0, 0,
                    ntpServerName[0].c_str(),
                    ntpServerName[1].c_str()
                    );
            while (!getLocalTime(&timeinfo)) {
                Serial.print("!");
            }
            break;

        case RTC_EXTERNE:
            if (rtc_externe->begin()) {
                new_time.tv_sec = rtc_externe->now().unixtime();
                new_time.tv_usec = 0;
                retour = settimeofday(&new_time, NULL);
            }else{
                retour = 1;
            }
            break;
    }

    // Définir la timezone 
    retour = setenv("TZ", timeZone.c_str(), 1);

    // Mettre à jour la variable d'environnement TZ
    tzset();

    if (retour == 0)
        return true;
    else
        return false;
}

/**
 * @brief Méthode pour actualiser 
 *        l'heure et la date contenus dans la rtc interne à l'ESP32
 * @param epoch
 * @return 0 si OK
 */
int DateTimeManager::setCurrentTime(unsigned long epoch) {

    int retour;
    struct timeval new_time;
    new_time.tv_sec = epoch;
    new_time.tv_usec = 0;

    retour = settimeofday(&new_time, NULL);

    return retour;
}

/**
 * @brief  Méthode pour obtenir le temps epoch courant de la rtc interne
 * @return le temps epoch 
 */
unsigned long DateTimeManager::getCurrentTime() const {

    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    return current_time.tv_sec;

}

/**
 * @brief Méthode pour écrire la date et l'heure calendaire locale
 *        en français. 
 * @param time_t Type arithmétique le nombre de secondes depuis 00h00, le 1er janvier 1970 (UTC)
 *        flux un objet dérivant de Stream (par exemple Serial) 
 */
void DateTimeManager::printDateTime(const time_t _time, Stream &flux) const {

    const char * months[] = {
        "Janv.", "Févr.", "Mars", "Avr.", "Mai", "Juin", "Juil.",
        "Août", "Sept.", "Oct.", "Nov.", "Déc."
    };

    const char * days[] = {
        "Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."
    };

    struct tm timeInfo;

    // convertit l'heure depuis l'époque en heure calendaire exprimée en heure locale
    localtime_r(&_time, &timeInfo);

    flux.printf("%s %d %s %d ",
            days[timeInfo.tm_wday],
            timeInfo.tm_mday,
            months[timeInfo.tm_mon],
            timeInfo.tm_year + 1900);

    flux.print(&timeInfo, "%H:%M:%S");
    flux.println(" CET");

}

/**
 * @brief  met à l'heure la rtc externe à partir de l'heure enregistrée
 *         dans la rtc interne.     
 * @return true si réussi
 */
bool DateTimeManager::set_RTC_Externe() {

    bool retour = false;
    if (rtc_externe->begin()) {
        time_t now;
        time(&now);
        rtc_externe->adjust(DateTime((uint32_t) now));
        retour = true;
    }
    printDateTime(rtc_externe->now().unixtime());
    return retour;
}



