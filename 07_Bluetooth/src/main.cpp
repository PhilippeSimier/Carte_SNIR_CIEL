/* 
 * File:   main.cpp
 * Author: philippe
 *
 * Created on 23 janvier 2024, 11:47
 */

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("CIEL_BT"); // Le nom du périphérique Bluetooth

  Serial.println("Le périphérique est prêt à être apparié.");
}

void loop() {
  if (SerialBT.available()) {
    // Lire les données Bluetooth
    char incomingByte = SerialBT.read();
    Serial.print("Donnée reçue: ");
    Serial.println(incomingByte);
  }

  // Envoyer des données Bluetooth
  if (Serial.available()) {
    char outgoingByte = Serial.read();
    SerialBT.print("Donnée envoyée: ");
    SerialBT.println(outgoingByte);
  }

  delay(20);
}


