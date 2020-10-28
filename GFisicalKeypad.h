
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

    /// Aggiorna il keypad applicando un algoritmo di debouncing
    /// ciclesUntilLast specifica il numero di aggiornamenti che ci devono essere tra un evento accettato e l'altro
    /// block_key indica all' algoritmo di bloccare i tasti tra un aggiornamento accettato e l'altro
    void updateDebounced(nat ciclesUntilLast, bool block_key = true);

    /// Aggiunge un pulsante al keypad
    void addButton(GFisicalButton *btn);

    /// Aggiunge un pulsante dato il nome, il pin e il gestore della pressione
    void addButton(char name[], nat pin, void (*handler)(GEvent *event));

    /// Restituisce un puntatore al pulsante select
    GFisicalButton* getSelectedBtn();

    /// Restituisce un puntatore al pulsante right
    GFisicalButton* getRightBtn();

    /// Restituisce un puntatore al pulsante left
    GFisicalButton* getLeftBtn();

    /// Restituisce un puntatore al pulsante up
    GFisicalButton* getUpBtn();

    /// Restituisce un puntatore al pulsante down
    GFisicalButton* getDownBtn();


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
    // Numero di aggiornamenti passati senza accettare eventi
    nat updates_until_last_event = 0;
    // Indica se nell' ultimo aggiornamento è stato attivato un pulsante
    bool last_update_activated_button = false;
};

#endif
