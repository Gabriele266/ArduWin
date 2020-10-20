/*
      Autore: Cavallo Gabriele
      Nome classe: GButton
      Descrizione classe: Rappresenta un pulsante in una interfaccia
      Progetto:ArduWin
*/

#ifndef FBTN_H
#define FBTN_H

#include "GControl.h"
#include "location.h"
#include "GIcon.h"
#include <Arduino.h>

/// Rappresenta un pulsante in ArduWin
class GButton : public GControl{
    public:
        /// Costruttore vuoto
        GButton();

		/// Costruttore per impostare il nome il testo e la posizione
		GButton(char name[], char content[], location pos);

		/// Costruttore che imposta nome e contenuto
		GButton(char __name[], char __content[]);

		/// Controlla gli eventi
		void updateEvents(location l);

		/// Inizializza l'icona nella memoria dello schermo
		bool begin();

		/// Attiva il pulsante
		void enable();

		/// Disattiva il pulsante
		void disable();

		/// Imposta l'icona
		void setIcon(GIcon* icn);

		/// Restituisce un puntatore all' icona
		GIcon* getIcon();

		/// Disegna il pulsante
		bool draw();

    private:
		// Numero di pressioni del pulsante
		unsigned int clicks;
		// Definisce se il pulsante è attivato
		bool enabled;
		// Rappresenta l'icona
		GIcon* icon = nullptr;
};

#endif
