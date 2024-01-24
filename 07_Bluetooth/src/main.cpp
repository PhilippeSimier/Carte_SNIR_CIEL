/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 23 janvier 2024, 11:47
 */

#include <BluetoothSerial.h>
#include <Afficheur.h>

BluetoothSerial SerialBT;
Afficheur afficheur;

void setup() {
    Serial.begin(115200);
    afficheur.init();
    SerialBT.begin("CIEL_BT1"); // Le nom du périphérique Bluetooth

    Serial.println("Le périphérique est prêt à être apparié.");
    afficheur.afficher("Bluetooth");
}

void loop() {

    // Lire les données Bluetooth pour les afficher
    char incomingByte;
    while (SerialBT.available()) {
        
        incomingByte = SerialBT.read();
        Serial.write(incomingByte);
        afficheur.afficher(incomingByte);
    }

    // Envoyer des données Bluetooth
    char outgoingByte;
    
    while (Serial.available()) {
        outgoingByte = Serial.read();
        SerialBT.write(outgoingByte);
    }

    delay(20);
}


