#ifndef FButton_CPP
#define FButton_CPP

#include "GButton.h"

GButton::GButton(){
	setText(" ");
	enabled = true;
}

GButton::GButton(char cont[], location loc){
	setText(cont);
	setLocation(loc);
	enabled = true;
}

GButton::GButton(char __content[]){
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
#ifdef ENABLE_SERIAL_ERRORS
	    launchError(" classe GButton. Tentativo di disegnare un controllo senza una superficie definita. ");
#ifdef ENABLE_SERIAL_INFO
	    writeReference();
#endif
	    closeLaunch();
#endif
        return false;
	}
}

#ifdef ENABLE_SERIAL_INFO
void GButton::writeReference() {
    Serial.print(F("Nome controllo: "));
    Serial.println(getName());
    Serial.print(F("Posizione controllo: "));
    Serial.println(toString(getLocation()));
    Serial.print(F("Testo controllo: "));
    Serial.println(getText());
}
#endif

bool GButton::begin() {
    // controllo che esista l'interfaccia
    if(getSurface() != nullptr){
        // Controllo che l'icona esista
        if (icon != nullptr) {
            __surf->createChar(icon->getIndex(), icon->getCode());
            return true;
        }
        else{
            #ifdef ENABLE_SERIAL_ERRORS
            launchError(" classe GButton. Tentativo di inizializzare un pulsante con icona senza una icona specificata. ");
            #ifdef ENABLE_SERIAL_INFO
            writeReference();
            #endif
            closeLaunch();
            #endif
            return false;
        }
    }
	else{
        #ifdef ENABLE_SERIAL_ERRORS
	    launchError(" classe GButton. Tentativo di inizializzare un pulsante con icona senza una superficie definita. ");
        #ifdef ENABLE_SERIAL_INFO
	    writeReference();
        #endif
	    closeLaunch();
        #endif
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
                    event->setSender("Button");
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
}

void GButton::enable()
{
	enabled = true;
}

void GButton::disable() {
	enabled = true;
}

#endif
