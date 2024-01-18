/* 
 * File:   DateTimeManager.cpp
 * Author: Philippe Simier Lycée Touchard Washington Le Mans
 * 
 * Created on 11 janvier 2024, 17:40
 */

#include <stdlib.h>

#include "DateTimeManager.h"

DateTimeManager::DateTimeManager() {

}

DateTimeManager::~DateTimeManager() {
}

int DateTimeManager::setCurrentTime(unsigned long epoch) {

    int retour;
    struct timeval new_time;
    new_time.tv_sec = epoch;
    new_time.tv_usec = 0;
    
    retour = settimeofday(&new_time, NULL); 

    // Définir la timezone sur Paris (Central European Time)
    retour = setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1); 

    // Mettre à jour la variable d'environnement TZ
    tzset();
    
    return retour;

}

/**
 * @brief  Méthode pour obtenir le temps epoch courant de la rtc
 * @return le temps epoch 
 */
unsigned long DateTimeManager::getCurrentTime() const {
    
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
    return current_time.tv_sec;
    
}

/**
 * @brief Méthode pour écrire la date et l'heure locale courante
 *        en français. 
 * @param flux un objet dérivant de Stream (par exemple Serial) 
 */
void DateTimeManager::printCurrentTime(Stream &flux) const {

    const char * months[] = {
        "Janv.", "Févr.", "Mars", "Avr.", "Mai", "Juin", "Juil.",
        "Août", "Sept.", "Oct.", "Nov.", "Déc."
    };

    const char * days[] = {
        "Dim.", "Lun.", "Mar.", "Mer.", "Jeu.", "Ven.", "Sam."
    };

    struct tm timeInfo;

    // time_t Type arithmétique le nombre de secondes 
    // depuis 00h00, le 1er janvier 1970 UTC
    time_t now;

    // renvoie l'heure actuelle du système  
    // sous forme de temps depuis l'époque
    time(&now);


    // convertit l'heure depuis l'époque en heure calendaire exprimée en heure locale
    localtime_r(&now, &timeInfo);

    flux.printf("%s %d %s %d ",
            days[timeInfo.tm_wday],
            timeInfo.tm_mday,
            months[timeInfo.tm_mon],
            timeInfo.tm_year + 1900);

    flux.println(&timeInfo, "%H:%M:%S CET");

}



