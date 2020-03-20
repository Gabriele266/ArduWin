/*classe generata dal programma CodeUtils di Gabriele Cavallo. 
La seguente classe contiene un costruttore.
      Autore: Cavallo Gabriele
      Versione: 1.1
      Tipologia licenza: Shareware
      Descrizione licenza: Shareware
      Nome classe: Label
      Descrizione classe: Rappresenta una etichetta in una interfaccia lcd
      Progetto: ArduCore
*/
#include "GControl.h"
#include <arduino.h>
#include "GIcon.h"
#include "Location.h"

#ifndef LABEL_H
#define LABEL_H

class GLabel : public GControl{
public:
	// Contruttore vuoto
    GLabel();
	// Costruttore che imposta il nome e il testo
	GLabel(char name[], char text[]);
	// Construttore che imposta il nome il testo e la posizione
	GLabel(char name[], char text[], location loc);
	
	// Funzione per mostrarlo
	// Ridefinizione del metodo virtuale
	bool draw();
	// Inizializza l'icona impostata 
	void begin();
	void updateEvents(location l);

	void setIcon(GIcon *icn);
private: 
	// Punta all' icona
	GIcon *icon;
};

#endif