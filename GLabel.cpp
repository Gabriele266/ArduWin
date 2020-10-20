#ifndef Label_CPP
#define Label_CPP

#include "GLabel.h"

GLabel::GLabel(){
	icon = nullptr;
}

GLabel::GLabel(char name[], char text[]) : GLabel(){
	setName(name);
	setText(text);
}

GLabel::GLabel(char name[], char text[], location l) : GLabel(){
	setName(name);
	setText(text);
	setLocation(l);
}

bool GLabel::begin() {
    // controllo che esista la superficie
    if(getSurface() != nullptr){
        // Controllo che l'icona esista
        if (icon != nullptr && !icon->isEmpty()) {
            __surf->createChar(icon->getIndex(), icon->getCode());
            return true;
        }
        else{
            return false;
        }
    }
    return false;
}

void GLabel::setIcon(GIcon* icn) {
	icon = icn;
}

bool GLabel::draw(){
    // controllo che esista la superficie
    if(getSurface() != nullptr){
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
        return true;
    }
    return false;
}

void GLabel::updateEvents(location l){
	// Non ci sono eventi
}
#endif
