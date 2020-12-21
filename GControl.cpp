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

bool GControl::draw(){

}

void GControl::setText(char _t[]){
    // Calcolo le dimensioni dei controlli
    byte old_dimension = (byte) strlen(__text);
    byte new_dimension = (byte) strlen(_t);

    // COntrollo che la nuova dimensione non sia maggiore della dimensione massima del testo per un controllo
    if(new_dimension < CONTROL_MAX_TXT_DIM){
        // Posso continuare
        // Ridisegno il controllo
        // Controllo che il controllo prima avesse del testo
        if(old_dimension > 0){
            // Controllo se la vecchia dimensione era più grande di quella corrente
            if(old_dimension > new_dimension){
                // Punto di partenza
                byte start = __point.x;
                // y di partenza
                byte y = __point.y;

                // Calcolo la posizione finale della pulizia
                byte end = start + old_dimension;

                // Scorro i caratteri tra start e end
                for(int index = start; index < end; index++){
                    // Metto uno spazio
                    __surf->setCursor(index, y);
                    __surf->print(" ");
                }
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
    else{
        // Non faccio niente, e' un errore

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






