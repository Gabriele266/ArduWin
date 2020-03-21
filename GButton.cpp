#ifndef FButton_CPP
#define FButton_CPP

#include "GButton.h"

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
        __surf->setCursor(getLocation().x -1, getLocation().y);
	// Controllo se devo mettere una icona
	if (icon != nullptr && !icon->isEmpty()) {
		// Disegno l'icona
		__surf->write(byte(icon->getIndex()));
	}
        // Disegno il testo
		__surf->print("|");
        __surf->print(__text);
		__surf->print("|");
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
	// GControllo se sono stato premutoi
	if(enabled){
		if(exists(l) && exists(getLocation()) && isInArea(l, getLocation(), strlen(__text))){
			 //Sono stato premutoi
			 // Creo un evento
			 GEvent *event = new GEvent();
			 // Imposto il nome
			 event->setName("buttonClick");
			 // Imposto il sender
             event->setSender(this->getName());
             // Imposto la posizione
             //event->setPosition(this->getLocation());
             // Imposto l'evento come gestito
             //event->throwEvent();
			 //Chiamo l'handler
             eventHandler(event);

			return;
		}
		else{
			return;
		}
	}
	else{

	}
	Serial.println("Controllo eventi pulsante");
}

void GButton::enable()
{
	enabled = true;
}

void GButton::disable() {
	enabled = true;
}
#endif
