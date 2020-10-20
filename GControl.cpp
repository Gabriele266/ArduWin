/*
=================================================
QUESTO FILE E' PARTE DEL PROGETTO SVEGLIA ARDUINO.
NON E' OPENSOURCE QUINDI E' ILLEGALE MODIFICARE IL CODICE
AUTORE: CAVALLO GABRIELE
IL FILE E TUTTO IL PROGETTO SONO PROTETTI DA COPYRIGHT.
E' INOLTRE ILLEGALE COPIARE LE IDEE E LE METODOLOGIE DI RISOLUZIONE DEI PROBLEMI
PER ULTERIORI INFORMAZIONI RIVOLGETEVI A GABRIELE CAVALLO:
3317375441
=================================================

Descrizione: implementazione della classe GControl, che rappresenta un GControllo all' interno della interfaccia.

*/


#ifndef GControl_CPP
#define GControl_CPP

// HEADER
#include "GControl.h"

GControl::GControl(){
    __surf = nullptr;
}

void GControl::setName(char _n[]){
    strcpy(__name, _n);
}

GControl::GControl(char name[], char text[]) : GControl(){
	// Salvo il valore del nome
	strcpy(__name, name);
	strcpy(__text, text);
}

GControl::GControl(char name[], char text[], location loc) : GControl(){
    // Salvo il nome
    strcpy(__name, name);
    // Salvo il testo
    strcpy(__text, text);
    // Salvo la posizione
    __point = loc;
}

char* GControl::getName(){
    return __name;
}

void GControl::setText(char _t[]){
    strcpy(__text , _t);
}

char* GControl::getText(){
    return __text;
}

void GControl::setTags(char _t[]){
    strcpy(__tags , _t);
}

char* GControl::getTags(){
    return __tags;
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

// Funzione fittizia
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

bool GControl::getShownState(){
    return __isShown;
}
#endif






