/*
      Autore: Cavallo Gabriele
      Descrizione classe: Rappresenta una etichetta in una interfaccia lcd
      Progetto: ArduWin
*/

#include "GControl.h"
#include <Arduino.h>
#include "GIcon.h"
#include "location.h"

#ifndef LABEL_H
#define LABEL_H

/// Rappresenta una etichetta in ArduWin
class GLabel : public GControl{
public:
	/// Contruttore vuoto
    GLabel();

	/// Costruttore che imposta il nome e il testo
	GLabel(char name[], char text[]);

	/// Construttore che imposta il nome il testo e la posizione
	GLabel(char name[], char text[], location loc);

	/// Funzione per mostrarlo
	/// Ridefinizione del metodo virtuale
	bool draw();

	/// Inizializza l'icona impostata
	bool begin();

	/// Aggiorna gli eventi
	void updateEvents(location l);

    /// Imposta l'icona della etichetta
	void setIcon(GIcon *icn);
private:
	// Punta all' icona
	GIcon *icon = nullptr;
};

#endif
