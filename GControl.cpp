/*
implementazione della classe GControl, che rappresenta un Controllo all' interno della interfaccia.

*/

#ifndef GControl_CPP
#define GControl_CPP

// HEADER
#include "GControl.h"

// Metodi per impostare la superficie
#if defined ARDUWIN_USE_I2C
// Versione per l'utilizzo con schermi lcd i2c
void GControl::setSurface(LiquidCrystal_I2C *s){
    __surf = s;
}
LiquidCrystal_I2C* GControl::getSurface(){
    return __surf;
}
#else
// Versione per l'utilizzo con schermi lcd normali
void GControl::setSurface(LiquidCrystal *s){
    __surf = s;
}
LiquidCrystal* GControl::getSurface(){
   return __surf;
}
#endif

GControl::GControl(){
    __surf = nullptr;
}

void GControl::setText(char _t[]){
    // Ridisegno il controllo
    if(strlen(__text) > 0){
        // Mantengo la vecchia dimensione
        unsigned int old_dimension = strlen(__text);

        // pulisco i caratteri
        for(int x = __point.x; x <= (old_dimension + __point.x); x++){
            // imposto il cursore e cancello il carattere
            __surf->setCursor(x, __point.y);
            // cancello
            __surf->print(" ");
        }
        // Imposto il testo
        strcpy(__text , _t);
        // Disegno il controllo
        draw();
    }
    else{
        // Imposto il testo
        strcpy(__text , _t);
    }
}

char* GControl::getText(){
    return __text;
}

void GControl::setLocation(location l){
    __point = l;
}

void GControl::setLocation(int x, int y){
    // creo una struct location con i valori dati
    location p;
    p.x = x;
    p.y = y;
    // Assegno
    __point = p;
}

location GControl::getLocation(){
    return __point;
}

bool GControl::draw(){

}

void GControl::setEventHandler(void (*ptr)(GEvent *event)){
	eventHandler = ptr;
}

void GControl::updateEvents(location l){
	// Niente

}

void GControl::callHandler(GEvent *event){
	// GControllo che esista
	if(eventHandler != nullptr){
		eventHandler(event);
	}
	else{

	}
}

bool GControl::isVisible(){
    return __isShown;
}
#endif






