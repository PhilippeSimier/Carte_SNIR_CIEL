# ESP32  Bluetooth 

## Description
Le module ESP32 offre une prise en charge **native du Bluetooth**, élargissant ainsi ses capacités de communication sans fil. Le Bluetooth est une technologie de communication courte portée largement utilisée pour connecter des périphériques électroniques entre eux de manière sans fil. L'intégration du Bluetooth sur l'ESP32 permet aux développeurs d'établir des liaisons sans fil avec d'autres dispositifs compatibles Bluetooth, tels que smartphones, ordinateurs portables et bien plus encore.

**Fonctionnalités clés du Bluetooth sur ESP32 :**

1.  **Compatibilité Bluetooth Classic et Bluetooth Low Energy (BLE) :** L'ESP32 prend en charge à la fois le Bluetooth Classic et le Bluetooth Low Energy, offrant une flexibilité dans le choix du protocole en fonction des exigences spécifiques du projet.
    
2.  **Communication bidirectionnelle :** Avec le Bluetooth sur l'ESP32, les développeurs peuvent établir des connexions bidirectionnelles, permettant l'échange de données entre l'ESP32 et d'autres appareils compatibles Bluetooth.
    
3.  **Création de périphériques Bluetooth :** L'ESP32 peut être configuré pour agir en tant que périphérique Bluetooth, permettant ainsi à d'autres appareils de le détecter et d'établir une connexion.

**Exemple d'utilisation :**

Un exemple courant d'utilisation du Bluetooth sur ESP32 est la création d'une liaison sans fil entre l'ESP32 et un smartphone. Cela permet de contrôler l'ESP32 à distance ou d'échanger des données entre les deux dispositifs.
```cpp
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
Afficheur afficheur;

void setup() {
    Serial.begin(115200);
    afficheur.init();
    SerialBT.begin("CIEL_BT1"); // Le nom du périphérique Bluetooth

    Serial.println("Le périphérique est prêt à être apparié.");
}

void loop() {

    // Lire les données Bluetooth pour les afficher
    char incomingByte;
    while (SerialBT.available()) {     
        incomingByte = SerialBT.read();
        Serial.write(incomingByte);
    }

    // Envoyer des données Bluetooth
    char outgoingByte;
    
    while (Serial.available()) {
        outgoingByte = Serial.read();
        SerialBT.write(outgoingByte);
    }

    delay(20);
}
```
Cet exemple crée un périphérique Bluetooth avec le nom "CIEL_BT1".  Le programme réalise un pont bidirectionnel entre la liaison Serial et la liaison bluetooth SerialBT.
Le programme écoute en permanence les données reçues du module Bluetooth et envoie les données saisies par le moniteur série  via la liaison Bluetooth.

# Changelog

 **24/01/2024 :**  Création du README.md 



> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)

<!-- TOOLBOX 

Génération des badges : https://shields.io/
Génération de ce fichier : https://stackedit.io/editor#


