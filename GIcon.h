/*classe generata dal programma CodeUtils di Gabriele Cavallo.
La seguente classe contiene un costruttore.
      Autore: Cavallo Gabriele
      Versione: 1.1
      Tipologia licenza: GPL
      Descrizione licenza: GPL
      Nome classe: GWinList
      Descrizione classe: Rappresenta una lista di finestre gestite.
      Progetto: Sveglia Arduino
*/
#ifndef ICON_H
#define ICON_H

// Header necessari
// Libreria per Arduino
#include <Arduino.h>        // Utilizzata per la definizione di byte

class GIcon {
public:
    // Costruttore vuoto
    GIcon();
    // Costruttore che accetta nome e codice
    GIcon(char name[], byte *c);
    // Costruttore che accetta nome, codice e indice
    GIcon(char name[], byte *code, int index);

    // Imposta il nome
    void setName(char name[]);
    // Restituisce il nome
    char* getName();

    // Imposta il codice
    void setCode(byte *arr);
    // Restituisce il codice
    byte* getCode();

    // Imposta l'indice
    void setIndex(int val);
    // restituisce l'indice
    int getIndex();

    // Restituisce true se l'icona è vuota
    bool isEmpty();

    // Funzione statica che permette la creazione di un icona in modo diretto
    static GIcon createIcon(byte arr[8], int indexIn);

private:
    // Nome della icona
    char name[20];
    // Codice della icona
    byte *code = nullptr;
    // Inidice della icona
    int index = 0;
};

#endif