#include "GNotification.h"

GNotification::GNotification()
{
    //ctor
}

GNotification::GNotification(char ti[], char t[]){
    strcpy(text, t);
    strcpy(title, ti);
}

GNotification::GNotification(char t[], char ti[], LiquidCrystal_I2C *s){
    strcpy(text, t);
    strcpy(title, ti);
    surf = s;
}

void GNotification::setText(char txt[]){
    strcpy(text, txt);
}

char* GNotification::getText(){
    return text;
}

void GNotification::setTitle(char ti[]){
    strcpy(title, ti);
}

char* GNotification::getTitle(){
    return title;
}

void GNotification::setSurface(LiquidCrystal_I2C* s){
    surf = s;
}

LiquidCrystal_I2C* GNotification::getSurface(){
    return surf;
}

bool GNotification::draw(){
    // controllo che lo schermo esista
    if(surf != 0x00){
        // Pulisco lo schermo
        surf->clear();

        // posiziono il titolo
        // controllo che esista
        if(strcmp(title, "") != 0){
            surf->setCursor(5,0);
            surf->print(title);
        }

        // Posiziono il testo
        // controllo che esista
        if(strcmp(text, "") != 0){
            // metto il tutto
            surf->setCursor(2,1);
            surf->print(text);
        }

        // posiziono il pulsante ok
        surf->setCursor(14, 3);
        surf->print("-OK-");

        return true;
    }
    else{
        return false;
    }
}

void GNotification::setHandler(void(* ha)(void)){
    handle = ha;
}

bool GNotification::update(unsigned int x, unsigned int y){
    // controllo se esiste un gestore
    if(handle != nullptr){
        // controllo la posizione
        if(x >= 14 && x <= 18 && y == 3){
            handle();
            return true;
        }
    }
    return false;
}
