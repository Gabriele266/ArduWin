/*
	Autore: cavallo gabriele
	Rappresenta un pulsante fisico in ambiente ArduWin
*/

#ifndef BUTTON_H_
#define BUTTON_H_

// Header di Arduino
#include <Arduino.h>
// Header della libreria base di ArduWin
#include "../ArduWin/ArduWin.h"

/// Rappresenta un numero naturale
typedef unsigned int nat;

/// Rappresenta un pulsante fisico
class GFisicalButton{
public:
	/// Costruttore vuoto
	GFisicalButton();

	/// Costruttore con un pin
	GFisicalButton(nat pin);

	/// Imposta il pin del pulsante
	void attachPin(nat val);

	/// Restituisce il pin a cui il pulsante è collegato
	nat getPin();

	/// Determina se il pulsante è premuto
	bool isPressed();

	/// Aggiorna il pulsante e, se è stato premuto, chiama l'handler
	void update();

	/// Inizializza il pulsante
	bool init();
	
	/// Abilita il pulsante per il controllo
	void enable(){
		active = true;
	}

	/// Disabilita il pulsante per il controllo
	void disable(){active = false;}

	/// Determina se il pulsante è attivo
	bool isEnabled(){return active;}

	/// Restituisce il valore della lettura sul pin del pulsante
	nat readOnPin();

#ifdef ENABLE_SERIAL_INFO
	/// Mostra informazioni sul pulsante utilizzando il seriale
	void writeReference();
#endif
private:
	// Pin a cui è collegato il pulsante
	nat pin = 0;
	// Determina se il pulsante è premuto
	bool pressed = false;
	// Determina se il pulsante è attivo
	bool active = true;
	// Puntatore alla funzione che gestisce la sua pressione
	void (*handler)() = nullptr;
};



#endif /* BUTTON_H_ */
