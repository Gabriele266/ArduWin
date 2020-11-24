//
// Created by Gabriele on 24/10/2020.
// Progetto: ArduWin
// Contiene le informazioni di esecuzione della libreria arduwin

#ifndef FLAGS_CPP
#define FLAGS_CPP

#include <Arduino.h>

// Sono nel target debug
// Do le impostazioni per arduwin
// Indica alla libreria di mostrare errori seriali in caso succedessero
//#define ENABLE_SERIAL_ERRORS

// Indica alla libreria di abilitare i warning seriali
//#define ENABLE_SERIAL_WARNINGS

// Indica alla libreria di abilitare le funzioni di informazioni sul seriale
//#define ENABLE_SERIAL_INFO

// Indica alla libreria che si desidera utilizzare le classi per la gestione dei dispositivi hardware
// Fa includere da arduwin anche gli header per il keypad, per i pulsanti
//#define ENABLE_HARDWARE_CONTROL

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
    #ifndef ENABLE_SERIAL_ERRORS
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


#endif