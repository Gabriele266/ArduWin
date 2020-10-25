//
// Created by Gabriele on 24/10/2020.
// Contiene le informazioni di esecuzione della libreria arduwin

#ifndef FLAGS_CPP
#define FLAGS_CPP

#include <Arduino.h>

// Indica alla libreria di mostrare errori seriali in caso succedessero
// Commentare per disabilitare il lancio degli errori sul seriale e ridurre l'utilizzo della sram
#define ENABLE_SERIAL_ERRORS

// Indica alla libreria di abilitare i warning seriali
<<<<<<< Updated upstream
// Commentare per disabilitare i warning seriali e ridurre l'utilizzo della sram
=======
>>>>>>> Stashed changes
#define ENABLE_SERIAL_WARNINGS

/// Invia un errore sul seriale
static void launchError(char text[]){
<<<<<<< Updated upstream
    Serial.println(F(""));
    Serial.print(F("/*Errore ArduWin: "));
    Serial.println(text);
=======
    Serial.println("");
    Serial.print("/*Errore ArduWin: ");
    Serial.println(text);
    
>>>>>>> Stashed changes
}

/// Invia un warning sul seriale
static void launchWarning(char text[]){
    Serial.println("");
<<<<<<< Updated upstream
    Serial.print(F("/*Warning ArduWin: "));
=======
    Serial.print("/*Warning ArduWin: ");
>>>>>>> Stashed changes
    Serial.println(text);
}

/// Invia un parametro sul seriale
static void launchParam(char name[], char value[]){
    Serial.print(name);
<<<<<<< Updated upstream
    Serial.print(F(":"));
=======
    Serial.print(":");
>>>>>>> Stashed changes
    Serial.println(value);
}

template <typename t>
<<<<<<< Updated upstream
static void launchParam(char name[], t value){
    Serial.print(name);
    Serial.print(F(":"));
=======
static void launchParam(char name[], t& value){
    Serial.print(name);
    Serial.print(":");
>>>>>>> Stashed changes
    Serial.println(value);
}

static void closeLaunch(){
<<<<<<< Updated upstream
    Serial.println(F("*/"));
=======
    Serial.println("*/");
>>>>>>> Stashed changes
}

#endif