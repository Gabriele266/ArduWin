//
// Created by Gabriele on 24/10/2020.
// Progetto: ArduWin
// Contiene le informazioni di esecuzione della libreria arduwin

#ifndef FLAGS_CPP
#define FLAGS_CPP

#include <Arduino.h>

// Indica alla libreria di mostrare errori seriali in caso succedessero
// Commentare per disabilitare il lancio degli errori sul seriale e ridurre l'utilizzo della sram
#define ENABLE_SERIAL_ERRORS

// Indica alla libreria di abilitare i warning seriali
// Commentare per disabilitare i warning seriali e ridurre l'utilizzo della sram
#define ENABLE_SERIAL_WARNINGS

// Indica alla libreria di abilitare le funzioni di informazioni sul seriale
// Commentare per non compilare le funzioni di invio informazioni
#define ENABLE_SERIAL_INFO

// # funzioni necessarie per inviare errori sul seriale
#ifdef ENABLE_SERIAL_ERRORS
/// Invia un errore sul seriale
static void launchError(char text[]){
    Serial.println(F(""));
    Serial.print(F("/*Errore ArduWin: "));
    Serial.println(text);
}

/// Invia un parametro sul seriale
static void launchParam(char name[], char value[]){
    Serial.print(name);
    Serial.print(F(":"));
    Serial.print(":");
    Serial.println(value);
}

template <typename t>
static void launchParam(char name[], t value) {
    Serial.print(name);
    Serial.print(F(":"));
    Serial.println(value);
}

/// Chiude il lancio di un errore
static void closeLaunch(){
    Serial.println(F("*/"));
}
#endif

// # funzioni necessarie per l'invio di warning seriale
#ifdef ENABLE_SERIAL_WARNINGS
/// Invia un warning sul seriale
static void launchWarning(char text[]){
    Serial.println("");
    Serial.print(F("/*Warning ArduWin: "));
    Serial.println(text);
}

/// Invia un parametro sul seriale
static void launchParam(char name[], char value[]){
    Serial.print(name);
    Serial.print(F(":"));
    Serial.print(":");
    Serial.println(value);
}

template <typename t>
static void launchParam(char name[], t value) {
    Serial.print(name);
    Serial.print(F(":"));
    Serial.println(value);
}

/// Chiude il lancio di un warning
static void closeLaunch(){
    Serial.println(F("*/"));
}
#endif


#endif