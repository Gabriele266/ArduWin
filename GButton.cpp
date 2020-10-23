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

bool GButton::draw() {
	// Disegno il pulsante
	// GControllo che sia stata impostate una superficie

	if (__surf != nullptr && enabled) {
		// Tolgo il blink
		__surf->noBlink();
		// Imposto il cursore
		__surf->setCursor(getLocation().x, getLocation().y);
		// Controllo se devo mettere una icona
		if (icon != nullptr) {
			// Disegno l'icona
			__surf->write(byte(icon->getIndex()));
		}
		// Disegno il testo
		__surf->print(__text);
		return true;
	}
	else{
        return false;
	}
}
bool GButton::begin() {
    // controllo che esista l'interfaccia
    if(getSurface() != nullptr){
        // Controllo che l'icona esista
        if (icon != nullptr) {
            __surf->createChar(icon->getIndex(), icon->getCode());
            return true;
        }
        else{
            return false;
        }
    }
	else{
        return false;
	}
}

void GButton::setIcon(GIcon* icn) {
	icon = icn;
}

GIcon* GButton::getIcon() {
	return icon;
}

void GButton::updateEvents(location l){
    // conrollo se esiste la superficie
    if(getSurface() != nullptr){
        // GControllo se sono stato premuto
        if(enabled){
            // Controllo che eistano tutti e che la posizione appartenga al pulsante
            if(exists(l) && exists(getLocation()) && isInArea(l,getLocation(), strlen(__text))){
                 //Sono stato premuto
                 // controllo se esiste il gestore eventi
                 if(eventHandler != nullptr){
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
                 }
            }
        }
    }
    else{
        return;
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
