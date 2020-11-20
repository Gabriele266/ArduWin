//
// Created by Gabriele on 20/11/2020.
//
#ifndef GTIMER_CPP
#define GTIMER_CPP

#include "GTimer.h"

GTimer::GTimer() {
    tick_time = 0;
    strcpy(name, "");
}

GTimer::GTimer(unsigned int time) {
    tick_time = time;
}

void GTimer::setTime(unsigned int val) {
    tick_time = val;
}

unsigned int GTimer::getTime(){
    return tick_time;
}

unsigned int GTimer::getCurrentTick() {
    return updates_since;
}

bool GTimer::update(){
    // Controllo se il timer è attivo
    if(activated){
        // Incremento il numero dei tick passati
        updates_since ++;
        // Controllo se è stato attivato il gestore
        if(updates_since == tick_time){
            // Attivo il gestore
            // Controllo che non sia nullo
            if(activatedManager != nullptr){
                activatedManager(tick_time, name);
                // Azzero il contatore
                updates_since = 0;
            }
        }
    }
    else{
        // Non eseguo niente
    }
}

void GTimer::setName(char *n){
    strcpy(name, n);
}

char* GTimer::getName(){
    return name;
}

void GTimer::setActivationHandler(void (*func)(unsigned int, char *)) {
    activatedManager = func;
}

void GTimer::start(){
    activated = true;
    // Azzero il numero di aggiornamenti
    updates_since = 0;
}

void GTimer::stop(){
    activated = false;
}

void GTimer::resume(){
    activated = true;
}

void GTimer::setState(bool s) {
    activated = s;
}

bool GTimer::getState(){
    return activated;
}

void GTimer::reset(){
    updates_since = 0;
}


#endif

