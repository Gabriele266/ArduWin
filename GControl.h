/*
	Autore: Cavallo Gabriele
	Versione: 1.1
	Progetto: ArduWin
	https://github.com/Gabriele266/ArduCore/blob/master/README.md
	Contiene l' interfaccia della classe GControl che rappresenta un controllo generico nella interfaccia
*/
#pragma once
// Inclusione
#include <Arduino.h>

// Controllo se devo utilizzare uno schermo lcd i2
#ifdef ARDUWIN_USE_I2C
// Libreria per gli schermi lcd I2C
#include <LiquidCrystal_I2C.h>
#else
// Utilizzo la libreria per schermi lcd normali
#include <LiquidCrystal.h>
#endif


// Header per la posizione
#include "Location.h"
// Header per gli eventi
#include "GEvent.h"

class GControl{
      public:
          // Costruttore di default
		GControl();

		GControl(char name[], char text[]);
        // Costruttore che accetta un
        GControl(char name[], char text[], location l);
		// Ottiene o imposta il nome del GControllo
		void setName(char _n[]);
		char* getName();

		// Ottiene o imposta il testo
		void setText(char _t[]);
		char* getText();

		// Ottiene o imposta i tag del GControllo
		void setTags(char _t[]);
		char* getTags();

		// Ottiene o imposta la posizione del GControllo
		void setLocation(location l);
		void setLocation(int x, int y);
		location getLocation();

		// Ottiene o imposta la surface su cui disegnare
		// Controllo quele libreria sto utilizzando
		#ifdef ARDUWIN_USE_I2C
		// Utilizzo quella per schermi i2c
		void setSurface(LiquidCrystal_I2C *s);
		LiquidCrystal_I2C* getSurface();
		#else
		// Utilizzo quella per schermi normali
		void setSurface(LiquidCrystal *s);
		LiquidCrystal* getSurface();
		#endif
		

		// Disegna il GControllo
		virtual bool draw();
		// Restituisce lo stato del GControllo
		bool getShownState();

		// Imposta il gestore degli eventi
		void setEventHandler(void (*ptr)(GEvent *event));
		// CHiama l'handler
		void callHandler(GEvent *event);

		// Funzione per aggiornare gli eventi
		virtual void updateEvents(location l);

		// Nome del controllo
		char __name[10];
		// Testo associato al controllo
		char __text[10];
		// Tag del controllo
		char __tags[10];
		// Posizione del controllo nella interfaccia
		location __point;
		// Surface per il disegno
		#ifdef ARDUWIN_USE_I2C
		LiquidCrystal_I2C *__surf;
		#else
		// Creo un puntatore all' oggetto della libreria normale
		LiquidCrystal *__surf;
		#endif
	
		// Definisce se l'oggetto è mostrato
		bool __isShown = false;
		// Puntatore a una funzione che gestisce gli eventi
		void (*eventHandler)(GEvent *event);
    private:


};
