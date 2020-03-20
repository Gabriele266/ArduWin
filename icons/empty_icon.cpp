/*
	Autore: Cavallo Gabriele
	Contenuto: Contiene una icona che rappresenta un orologio
	Licenza: GPL
*/
#ifndef CLOCK_ICON_INCLUDED
#define CLOCK_ICON_INCLUDED

// Header di Arduino
#include <Arduino.h>

// Rappresentazione dell' icona in un array di 8 elementi di byte
static byte clock_icon[8]{
     B00000,
     B01110,
     B10001,
     B10101,
     B10101,
     B10001,
     B01110,
     B00000
};

#endif
