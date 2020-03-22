#ifndef FButton_CPP
#define FButton_CPP

#include "GButton.h"
#include <Arduino.h>

GButton::GButton(){
	setName(" ");
	setText(" ");
	enabled = true;
}

GButton::GButton(char name[], char cont[], location loc){
	setName(name);
	setText(cont);
	setLocation(loc);
	enabled = true;
}

GButton::GButton(char __name[], char __content[]){
    setName(__name);
    setText(__content);
    enabled = true;
}

bool GButton::draw(){
	// Disegno il pulsante
	// GControllo che sia stata impostate una superficie
	if(__surf != nullptr && enabled){
        // Tolgo il blink
        __surf->noBlink();
        // Imposto il cursore
        __surf->setCursor(getLocation().x, getLocation().y);
	// Disegno una barra verticale
	
	// Controllo se devo mettere una icona
	if (icon != nullptr && !icon->isEmpty()) {
		// Disegno l'icona
		__surf->write(byte(icon->getIndex()));
	}
        // Disegno il testo
        __surf->print(__text);
	// Disegno un altra barra verticale
	
    	}
	else{
		
	}

}

void GButton::begin() {
	// Controllo che l'icona esista
	if (icon != nullptr && !icon->isEmpty()) {
		__surf->createChar(icon->getIndex(), icon->getCode());
	}
}

void GButton::setIcon(GIcon* icn) {
	icon = icn;
}

GIcon* GButton::getIcon() {
	return icon;
}


void GButton::updateEvents(location l){
	// GControllo se sono stato premuto
	if(enabled){
		// Controllo che eistano tutti e che la posizione appartenga al pulsante
		if(exists(l) && exists(getLocation()) && isInArea(l,getLocation(), strlen(__text))){
			 //Sono stato premuto
			 // Creo un evento
			 GEvent *event = new GEvent();
			 // Imposto il nome
			 event->setName("buttonClick");
			 // Imposto il sender
             		event->setSender(this->getName());
             		// Imposto la posizione
             		event->setPosition(this->getLocation());
             		// Imposto l'evento come gestito
             		event->throwEvent();
			 //Chiamo l'handler
             		eventHandler(event);
			
			return;
		}
	}
}

void GButton::enable()
{
	enabled = true;
}

void GButton::disable() {
	enabled = true;
}
#endif
