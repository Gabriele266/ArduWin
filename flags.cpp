//
// Created by Gabriele on 24/10/2020.
// Contiene le informazioni di esecuzione della libreria arduwin

#ifndef FLAGS_CPP

#define FLAGS_CPP

#include <Arduino.h>

// Indica alla libreria di mostrare errori seriali in caso succedessero
#define ENABLE_SERIAL_ERRORS

// Indica alla libreria di abilitare i warning seriali
#define ENABLE_SERIAL_WARNINGS

/// Invia un errore sul seriale
static void launchError(char text[]){
    Serial.println("");
    Serial.print("/*Errore ArduWin: ");
    Serial.println(text);
    
}

/// Invia un warning sul seriale
static void launchWarning(char text[]){
    Serial.println("");
    Serial.print("/*Warning ArduWin: ");
    Serial.println(text);
}

/// Invia un parametro sul seriale
static void launchParam(char name[], char value[]){
    Serial.print(name);
    Serial.print(":");
    Serial.println(value);
}

template <typename t>
static void launchParam(char name[], t& value){
    Serial.print(name);
    Serial.print(":");
    Serial.println(value);
}

static void closeLaunch(){
    Serial.println("*/");
}

#endif