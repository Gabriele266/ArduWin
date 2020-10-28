/*

*/
#ifndef FISICALBTN_CPP
#define FISICALBTN_CPP

#include "GFisicalButton.h"

GFisicalButton::GFisicalButton(){
	pin = 0;
	pressed = false;
}

GFisicalButton::GFisicalButton(nat p){
	pin = p;
}

GFisicalButton::GFisicalButton(char n[]){
    strcpy(name, n);
}

void GFisicalButton::setName(char *n) {
    strcpy(n, name);
}

char* GFisicalButton::getName(){
    return name;
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

bool GFisicalButton::isPressed(){
	if(readOnPin() > 900){
		return true;
	}
	else{
		return false;
	}
}

bool GFisicalButton::isPressed(nat custom_soil){
    if(readOnPin() > custom_soil){
        return true;
    }
    else{
        return false;
    }
}

void GFisicalButton::setPressHandler(void (*n)(GEvent *event)){
    handler = n;
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

#ifdef ENABLE_SERIAL_INFO
void GFisicalButton::writeReference() {
    Serial.print("Nome pulsante: ");
    Serial.println(name);
    Serial.print(F("Pulsante sul pin: "));
    Serial.println(pin);
}

void GFisicalButton::writeState(){
    Serial.print(F("Stato pulsante "));
    Serial.print(name);
    Serial.print(F(" : "));
    if(isPressed()){
        Serial.println(F("Premuto. "));
    }
    else{
        Serial.println(F("Non premuto. "));
    }
}
#endif



#endif