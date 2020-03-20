#ifndef Label_CPP
#define Label_CPP

#include "GLabel.h"

GLabel::GLabel(){
	
}

GLabel::GLabel(char name[], char text[]){
	setName(name);
	setText(text);
}

GLabel::GLabel(char name[], char text[], location l){
	setName(name);
	setText(text);
	setLocation(l);
}

void GLabel::begin() {
	// Controllo che l'icona esista
	if (icon != nullptr && !icon->isEmpty()) {
		__surf->createChar(icon->getIndex(), icon->getCode());
	}
}

void GLabel::setIcon(GIcon* icn) {
	icon = icn;
}

bool GLabel::draw(){
	// Tolgo il blink
	__surf->noBlink();
	// Imposto il cursore
	__surf->setCursor(getLocation().x, getLocation().y);
	// Controllo se devo mettere una icona
	if (icon != nullptr && !icon->isEmpty()) {
		// Disegno l'icona
		__surf->write(byte(icon->getIndex()));
	}
	// Disegno il testo
	__surf->print(__text);
}

void GLabel::updateEvents(location l){
	// Non ci sono eventi
	
}
#endif
