/*
 *  Autore: Cavallo Gabriele
 *  Versione: 1.1
 *  Contiene l'implementazione della classe GIcon per la gestione delle icone nel progetto
 **/

#ifndef ICON_CPP
#define ICON_CPP

// Header di Arduino per byte
#include <Arduino.h>
// Interfaccia della classe
#include "GIcon.h"
// Header con le icone di default
#include "default_icons.h"

GIcon::GIcon() {
    // Costruttore vuoto
    // Inizializzo l'icona come empty icon
    code = nullptr;
}

GIcon::GIcon(char name[], byte* c) {
    // Salvo il nome
    strcpy(this->name, name);
    // Impostoil codice
    code = c;
}

GIcon::GIcon(char name[], byte* c, int i) {
	// Salvo il nome
	strcpy(this->name, name);
	// Impostoil codice
	code = c;
    // Imposto l'indice
    index = i;
}

void GIcon::setName(char n[]) {
    strcpy(name, n);
}

char* GIcon::getName() {
    return name;
}

void GIcon::setCode(byte *arr) {
    code = arr;
}

byte* GIcon::getCode() {
    return code;
}

void GIcon::setIndex(int val) {
    // Controllo il valore
    if (val >= 0) {
        // Va bene
        index = val;
    }
}

int GIcon::getIndex() {
    return index;
}

GIcon GIcon::createIcon(byte arr[8], int indexIn) {
    GIcon res;
    res.setCode(arr);
    res.setIndex(indexIn);

    return res;
}

bool GIcon::isEmpty() {
    if (code != nullptr) {
        // Controllo se è vuoto
        for (int x = 0; x < 8; x++) {
            if (code[x] == B00000) {
                return false;
            }
        }
        return true;
    }
    else {
        return true;
    }
}

#endif
