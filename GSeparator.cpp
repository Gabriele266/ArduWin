//
// Created by Gabriele on 28/10/2020.
//

#include "GSeparator.h"

GSeparator::GSeparator(){
    // Cancello gli elementi della stringa che non servono
    for(int x = 15; x > 2; x--){
        //delete &__text[x];
    }
}

GSeparator::GSeparator(char t){
    __text[0] = t;
}

bool GSeparator::draw(){
    // Controllo la superficie
    if(getSurface() != nullptr){
        getSurface()->setCursor(getLocation().x, getLocation().y);
        getSurface()->print(__text);
    }
}