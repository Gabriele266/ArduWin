/*
	Autore: Cavallo Gabriele
	Progetto: ArduWin
	https://github.com/Gabriele266/ArduCore/blob/master/README.md
	Contiene l' interfaccia della classe GControl che rappresenta un controllo generico nella interfaccia
*/

#pragma once
// Inclusione
#define ARDUWIN_USE_I2C
#include <Arduino.h>

// Controllo se devo utilizzare uno schermo lcd i2
#if defined ARDUWIN_USE_I2C
// Libreria per gli schermi lcd I2C
#include <LiquidCrystal_I2C.h>
#else
// Utilizzo la libreria per schermi lcd normali
#include <LiquidCrystal.h>
#endif

// Header per la posizione
#include "location.h"
// Header per gli eventi
#include "GEvent.h"

/// Rappresenta un controllo in ambiente ArduWin
class GControl{
public:
    // Costruttore di default
    GControl();
    /// Costruttore di base con nome e testo
    GControl(char text[]);

    /// Costruttore che accetta un
    GControl(char text[], location l);

    /// Ottiene o imposta il testo
    void setText(char _t[]);
    char* getText();

    /// Ottiene o imposta la posizione del GControllo
    void setLocation(location l);

    /// Imposta la posizione in base ad una coppia di coordinate
    void setLocation(int x, int y);

    /// Restituisce la posizione del controllo
    location getLocation();

    // Ottiene o imposta la surface su cui disegnare
    // Controllo quele libreria sto utilizzando
    #if defined ARDUWIN_USE_I2C
    // Utilizzo quella per schermi i2c
    void setSurface(LiquidCrystal_I2C *s);
    LiquidCrystal_I2C* getSurface();
    #else
    // Utilizzo quella per schermi normali
    void setSurface(LiquidCrystal *s);
    LiquidCrystal* getSurface();
    #endif

    /// Disegna il GControllo. Restituisce true se l'operazione è andata a buon fine
    virtual bool draw();

    /// Restituisce true se il controllo è visibile
    bool isVisible();

    /// Imposta il gestore degli eventi
    void setEventHandler(void (*ptr)(GEvent *event));

    /// CHiama l'handler
    void callHandler(GEvent *event);

    /// Funzione per aggiornare gli eventi
    virtual void updateEvents(location l);

    /// Testo associato al controllo
    char __text[10];

    /// Posizione del controllo nella interfaccia
    location __point = createLocation();

    /// Definisce se l'oggetto è mostrato
    bool __isShown = false;

    /// Puntatore a una funzione che gestisce gli eventi
    void (*eventHandler)(GEvent *event);

    /// Surface per il disegno
#if defined ARDUWIN_USE_I2C
    LiquidCrystal_I2C *__surf = nullptr;
#else
    // Creo un puntatore all' oggetto della libreria normale
		LiquidCrystal *__surf = nullptr;
#endif


    private:


};
