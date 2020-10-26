/*

*/
#include "GFisicalButton.h"

GFisicalButton::GFisicalButton(){
	pin = 0;
	pressed = false;
}

GFisicalButton::GFisicalButton(nat p){
	pin = p;
}

void GFisicalButton::attachPin(nat p){
	// Controllo che il pin esista e non sia seriale
	if(p > 0 && p < 90){
		pin = p;
	}
	else{
		#ifdef ENABLE_SERIAL_ERRORS
		launchError(" classe GFisicalButton. Tentativo di impostare un pin non esistente o dedicato al seriale. ");
		launchParam("Pin", p);
		closeLaunch();
		#endif
	}
}

nat GFisicalButton::getPin(){
	return pin;
}

bool GFisicalButton::isPressed(){
	if(readOnPin() > 900){
		return true;
	}
	else{
		return false;
	}
}

bool GFisicalButton::init(){
	// controllo che il pin esista
	if(pin != 0){
		pinMode(pin, INPUT);
		analogWrite(0, pin);
		return true;
	}
	else{
#ifdef ENABLE_SERIAL_ERRORS
	    launchError(" classe GFisicalButton. Tentativo di inizializzare un pulsante con un pin non valido o non specificato. ");
	    launchParam("Valore pin", pin);
	    closeLaunch();
#endif
		return false;
	}
}

#ifdef ENABLE_SERIAL_WARNINGS
void GFisicalButton::writeReference() {
    Serial.print(F("Pulsante sul pin: "));
    Serial.println(pin);
}
#endif

nat GFisicalButton::readOnPin(){
	// controllo il pin
	if(pin != 0){
		nat read = analogRead(pin);
		return read;
	}
	else{
		return 0;
		#ifdef ENABLE_SERIAL_ERRORS
		launchError(" classe GFisicalButton. Tentativo di lettura su un pin non esistente.");
		launchParam("Pin", pin);
		closeLaunch();
		#endif
	}
}