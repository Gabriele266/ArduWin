/*
      Autore: Cavallo Gabriele
      Nome classe: GButton
      Descrizione classe: Rappresenta un pulsante in una interfaccia
      Progetto:ArduWin
*/

#ifndef FBTN_H
#define FBTN_H

// Header per i controlli
#include "GControl.h"
// Header per le posizioni
#include "location.h"
// Header per le icone
#include "GIcon.h"
// Header di Arduino
#include <Arduino.h>
// Header per le modalità di esecuzione
#include "flags.cpp"

/// Rappresenta un pulsante in ArduWin
class GButton : public GControl{
    public:
        GButton();

		/// Costruttore per impostare il nome il testo e la posizione
		GButton(char content[], location pos);

		/// Costruttore che imposta nome e contenuto
		GButton(char __content[]);

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

#ifdef ENABLE_SERIAL_INFO
		/// Mostra informazioni sul controllo
		void writeReference();
#endif
    private:
		// Numero di pressioni del pulsante
		byte clicks;
		// Definisce se il pulsante è attivato
		bool enabled;
		// Rappresenta l'icona
		GIcon* icon = nullptr;
};

#endif
