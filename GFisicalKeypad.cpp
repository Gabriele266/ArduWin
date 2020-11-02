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

bool GFisicalKeypad::update(){
    // controllo che la winlist non sia nulla
    if(win_handler != nullptr){
////        // Controllo i pulsanti di default
        if(default_buttons[0]->isPressed()){
            win_handler->moveCursorRight();
            return true;
        }
        else if(default_buttons[1]->isPressed()){
            win_handler->moveCursorLeft();
            return true;
        }
        else if(default_buttons[2]->isPressed()){
            win_handler->moveCursorUp();
            return true;
        }
        else if(default_buttons[3]->isPressed()){
            win_handler->moveCursorDown();
            return true;
        }
        else if(default_buttons[4]->isPressed()){
            win_handler->get(win_handler->getCurrent())->updateControls(win_handler->getCursorPosition());
            return true;
        }
        else{
            return false;
        }
    }
}

void GFisicalKeypad::decalcFunction(nat number) {
    switch(number){
        case 0:
            win_handler->moveCursorRight();
            break;
        case 1:
            win_handler->moveCursorLeft();
            break;
        case 2:
            win_handler->moveCursorUp();
            break;
        case 3:
            win_handler->moveCursorDown();
            break;
        case 4:
            // chiamo il select
            win_handler->get(win_handler->getCurrent())->updateControls(win_handler->getCursorPosition());
            break;
    }
}

void GFisicalKeypad::updateDebounced(nat ciclesUntilLast, bool block_key) {
    // controllo i prerequisiti
    if(win_handler != nullptr) {
        if(updates_until_last_event == ciclesUntilLast){
            // controllo se supero il blocco
            if(!last_update_activated_button){
                // controllo se la azione è riferita ad un pulsante
                last_update_activated_button = update();
            }
            else{
                last_update_activated_button = false;
            }
            // azzero il contatore
            updates_until_last_event = 0;
        }
        else{
            updates_until_last_event ++;
        }
    }
}
#endif
