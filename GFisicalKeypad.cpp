#ifndef EXPANSION_KEYPAD_CPP
#include "GFisicalKeypad.h"

GFisicalKeypad::GFisicalKeypad(){
    win_handler = nullptr;
    for(int x = 0; x < 5; x++){
        // Creo il pulsante
        default_buttons.add(new GFisicalButton());
    }
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

#ifdef ENABLE_SERIAL_INFO
void GFisicalKeypad::writeReference() {

}
#endif

void GFisicalKeypad::update(){
    // controllo che la winlist non sia nulla
    if(win_handler != nullptr){
        // Controllo che tutti i pulsanti siano validi
        if(default_buttons.notEmpty()){
            // Controllo i pulsanti di default
            if(default_buttons[0]->isPressed()){
                win_handler->moveCursorRight();
            }
            else if(default_buttons[1]->isPressed()){
                win_handler->moveCursorLeft();
            }
            else if(default_buttons[2]->isPressed()){
                win_handler->moveCursorUp();
            }
            else if(default_buttons[3]->isPressed()){
                win_handler->moveCursorDown();
            }
            else if(default_buttons[4]->isPressed()){
                win_handler[win_handler->getCurrent()]->updateControls(win_handler->getCursorPosition());
            }
        }
        else{
#ifdef ENABLE_SERIAL_ERRORS
            launchError(" classe GFisicalKeypad. Tentativo di aggiornare il keypad senza aver definito tutti i pulsanti necessari. ");
            launchParam("Nome", name);
            closeLaunch();
#endif
        }
    }
    else{
#ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GFisicalKeypad. Tentativo di aggiornare il keypad senza una GWinList associata. ");
        launchParam("Nome", name);
        closeLaunch();
#endif
    }
}
#endif
