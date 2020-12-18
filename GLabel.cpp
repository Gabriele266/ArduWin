#ifndef Label_CPP
#define Label_CPP

#include "GLabel.h"

GLabel::GLabel(){
	icon = nullptr;
    __isShown = true;
}

GLabel::GLabel(char text[]) : GLabel(){
	strcpy(__text, text);
}

GLabel::GLabel(char text[], location l) : GLabel(){
	strcpy(__text, text);
	__point = l;
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
    if(getSurface() != nullptr && __isShown){
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

void GLabel::hide(){
    __isShown = false;
}

void GLabel::show(){
    __isShown = true;
}
#endif
