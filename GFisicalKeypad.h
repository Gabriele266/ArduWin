
/*
 * Autore: cavallo gabriele
 * Rappresenta un keypad in ArduWin
 */

#ifndef GKEYPAD_HEAD
#define GKEYPAD_HEAD

#include "GFisicalButton.h"
#include <ArduWin.h>

/// Rappresenta un keypad
class GFisicalKeypad{
public:
    GFisicalKeypad();

    /// Costruttore con il nome
    GFisicalKeypad(char name[]);

    /// Imposta il nome del keypad
    void setName(char n[]);

    /// Imposta il pin del pulsante right
    void setRightBtnPin(nat pin);

    /// Imposta il pin del pulsante left
    void setLeftBtnPin(nat pin);

    /// Imposta il pin del pulsante up
    void setUpBtnPin(nat pin);

    /// Imposta il pin del pulsante down
    void setDownBtnPin(nat pin);

    /// Imposta il pin di selezione
    void setSelectBtnPin(nat pin);

    /// Inizializza il keypad
    bool beginAll();

    /// Imposta il gestore delle finestre
    void attachWinList(GWinList *parent);

    /// Aggiorna il keypad, controlla le azioni da fare e le esegue
    void update();

    /// Aggiunge un pulsante al keypad
    void addButton(GFisicalButton *btn);

#ifdef ENABLE_SERIAL_INFO
    /// Mostra le informazioni del keypad sul seriale
    void writeReference();
    /// Mostra le informazioni di tutti i pulsanti e il loro stato corrente
    void writeState();
#endif

private:
    // Nome del keypad
    char name[10];

    // Array con i pulsanti di default
    // 0: right
    // 1: left
    // 2: up
    // 3: down
    // 4: select
    GArray<GFisicalButton, 5> default_buttons;

    // Array con i pulsanti aggiuntivi
    GArray<GFisicalButton, 5> additional_buttons;

    // Puntatore al gestore di finestre
    GWinList *win_handler = nullptr;
};

#endif
