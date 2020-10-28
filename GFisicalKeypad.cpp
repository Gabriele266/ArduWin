#ifndef EXPANSION_KEYPAD_CPP
#define EXPANSION_KEYPAD_CPP

#include "GFisicalKeypad.h"

GFisicalKeypad::GFisicalKeypad(){
    win_handler = nullptr;
    updates_until_last_event = 0;
    last_update_activated_button = false;
    // Creo i pulsanti e ne imposto i nomi
    default_buttons.add(new GFisicalButton("Right"));
    default_buttons.add(new GFisicalButton("Left"));
    default_buttons.add(new GFisicalButton("Up"));
    default_buttons.add(new GFisicalButton("Down"));
    default_buttons.add(new GFisicalButton("Select"));
}

GFisicalKeypad::GFisicalKeypad(char n[]) : GFisicalKeypad(){
    strcpy(name, n);
}

void GFisicalKeypad::setDownBtnPin(nat pin) {
    // imposto il pin
    default_buttons[2]->attachPin(pin);
}

void GFisicalKeypad::setUpBtnPin(nat pin) {
    default_buttons[3]->attachPin(pin);
}

void GFisicalKeypad::setLeftBtnPin(nat pin) {
    default_buttons[1]->attachPin(pin);
}

void GFisicalKeypad::setRightBtnPin(nat pin) {
    default_buttons[0]->attachPin(pin);
}

void GFisicalKeypad::setSelectBtnPin(nat pin) {
    default_buttons[4]->attachPin(pin);
}

bool GFisicalKeypad::beginAll(){
    for(int x = 0; x < 5; x++ ){
        default_buttons[x]->init();
    }
}

void GFisicalKeypad::attachWinList(GWinList *parent) {
    win_handler = parent;
}

void GFisicalKeypad::setName(char *n){
    strcpy(name, n);
}

GFisicalButton* GFisicalKeypad::getRightBtn(){
    return default_buttons[0];
}

GFisicalButton* GFisicalKeypad::getLeftBtn(){
    return default_buttons[1];
}

GFisicalButton* GFisicalKeypad::getUpBtn() {
    return default_buttons[2];
}

GFisicalButton* GFisicalKeypad::getDownBtn() {
    return default_buttons[3];
}

GFisicalButton* GFisicalKeypad::getSelectedBtn() {
    return default_buttons[4];
}

#ifdef ENABLE_SERIAL_INFO
void GFisicalKeypad::writeReference() {
    for(int x = 0; x < 5; x++){
        default_buttons[x]->writeReference();
    }
}

void GFisicalKeypad::writeState(){
    for(int x = 0; x < 5; x ++){
        default_buttons[x]->writeState();
    }
}
#endif

void GFisicalKeypad::update(){
    // controllo che la winlist non sia nulla
    if(win_handler != nullptr){
////        // Controllo i pulsanti di default
        if(default_buttons[0]->isPressed()){
            win_handler->moveCursorRight();
            last_update_activated_button = true;
        }
        else if(default_buttons[1]->isPressed()){
            win_handler->moveCursorLeft();
            last_update_activated_button = true;
        }
        else if(default_buttons[2]->isPressed()){
            win_handler->moveCursorUp();
            last_update_activated_button = true;
        }
        else if(default_buttons[3]->isPressed()){
            win_handler->moveCursorDown();
            last_update_activated_button = true;
        }
        else if(default_buttons[4]->isPressed()){
            win_handler->get(win_handler->getCurrent())->updateControls(win_handler->getCursorPosition());
            last_update_activated_button = true;
        }
        else{
            last_update_activated_button = false;
        }
    }
//    else{
//#ifdef ENABLE_SERIAL_ERRORS
//        launchError(" classe GFisicalKeypad. Tentativo di aggiornare il keypad senza una GWinList associata. ");
//        launchParam("Nome", name);
//        closeLaunch();
//#endif

}

void GFisicalKeypad::updateDebounced(nat ciclesUntilLast, bool block_key) {
    // controllo i prerequisiti
    if(win_handler != nullptr){
        // controllo se è passato il numero giusto di aggiornamenti
        if(updates_until_last_event == ciclesUntilLast){
            // controllo se ci sono pulsanti premuti
            if(default_buttons[0]->isPressed()){
                // pulsante right premuto
                // controllo se devo usare un blocco
                if(block_key){
                    // controllo se l'istruzione precedente aveva attivato un pulsante
                    if(!last_update_activated_button){
                        // posso eseguire l'istruzione
                        // muovo il cursore a destra
                        win_handler->moveCursorRight();
                        // attivo il flag
                        last_update_activated_button = true;
                    }
                }
                else{
                    // eseguo l'istruzione
                    win_handler->moveCursorRight();
                }
                // azzero il contatore degli aggiornamenti
                updates_until_last_event = 0;
            }
            else if(default_buttons[1]->isPressed()){
                // pulsante right premuto
                // controllo se devo usare un blocco
                if(block_key){
                    // controllo se l'istruzione precedente aveva attivato un pulsante
                    if(!last_update_activated_button){
                        // posso eseguire l'istruzione
                        // muovo il cursore a destra
                        win_handler->moveCursorLeft();
                        // attivo il flag
                        last_update_activated_button = true;
                    }
                }
                else{
                    // eseguo l'istruzione
                    win_handler->moveCursorLeft();
                }
                // azzero il contatore degli aggiornamenti
                updates_until_last_event = 0;
            }
            else if(default_buttons[2]->isPressed()){
                // pulsante right premuto
                // controllo se devo usare un blocco
                if(block_key){
                    // controllo se l'istruzione precedente aveva attivato un pulsante
                    if(!last_update_activated_button){
                        // posso eseguire l'istruzione
                        // muovo il cursore a destra
                        win_handler->moveCursorUp();
                        // attivo il flag
                        last_update_activated_button = true;
                    }
                }
                else{
                    // eseguo l'istruzione
                    win_handler->moveCursorUp();
                }
                // azzero il contatore degli aggiornamenti
                updates_until_last_event = 0;
            }
            else if(default_buttons[3]->isPressed()){
                // pulsante right premuto
                // controllo se devo usare un blocco
                if(block_key){
                    // controllo se l'istruzione precedente aveva attivato un pulsante
                    if(!last_update_activated_button){
                        // posso eseguire l'istruzione
                        // muovo il cursore a destra
                        win_handler->moveCursorDown();
                        // attivo il flag
                        last_update_activated_button = true;
                    }
                }
                else{
                    // eseguo l'istruzione
                    win_handler->moveCursorDown();
                }
                // azzero il contatore degli aggiornamenti
                updates_until_last_event = 0;
            }
            else if(default_buttons[4]->isPressed()){
                // pulsante right premuto
                // controllo se devo usare un blocco
                if(block_key){
                    // controllo se l'istruzione precedente aveva attivato un pulsante
                    if(!last_update_activated_button){
                        // posso eseguire l'istruzione
                        // lancio il select
                        win_handler->get(win_handler->getCurrent())->updateControls(win_handler->getCursorPosition());
                        // attivo il flag
                        last_update_activated_button = true;
                    }
                }
                else{
                    // eseguo l'istruzione
                    win_handler->get(win_handler->getCurrent())->updateControls(win_handler->getCursorPosition());
                }
                // azzero il contatore degli aggiornamenti
                updates_until_last_event = 0;
            }
            // nessun tasto premuto
            else{
                // azzero il flag
                last_update_activated_button = false;
            }

            // azzero il contatore
            updates_until_last_event = 0;
        }
        else{
            // incremento il contatore
            updates_until_last_event ++;
        }
    }
}
#endif
