//
// Created by Gabriele on 20/11/2020.
//

#ifndef ARDUWIN_GTIMER_H
#define ARDUWIN_GTIMER_H

#include <Arduino.h>

/// Rappresenta un timer per l'esecuzione di una funzione
class GTimer {
public:
    GTimer();

    /// Inizializza il timer con un intervallo tra una attivazione e l'altra
    GTimer(unsigned int time);

    /// Imposta il tempo di attivazione
    void setTime(unsigned int val);

    /// Restituisce il tempo di attivazione (tempo tra una attivazione e l'altra)
    unsigned int getTime();

    /// Restituisce il numero di tick che sono avvenuti dalla scorsa attivazione
    unsigned int getCurrentTick();

    /// Aggiorna il timer
    bool update();

    /// Imposta il nome del timer
    void setName(char name[]);

    /// Restituisce il nome del timer
    char* getName();

    /// Imposta il gestore della attivazione
    void setActivationHandler(void (*func)(unsigned int, char *));

    /// Avvia il timer e resetta il numero di aggiornamenti
    void start();

    /// Disabilita il timer
    void stop();

    /// Riavvia il timer mantenendo il numero di aggiornamenti già passati
    void resume();

    /// Imposta lo stato di attivazione del timer
    void setState(bool s);

    /// Restituisce lo stato del timer
    bool getState();

    /// Resetta il timer (riporta il numero di aggiornamenti a 0)
    void reset();

private:
    // Numero di tick che devono passare tra una attivazione e l'altra
    unsigned int tick_time;
    // Nome del timer
    char name[11];
    // Gestore della attivazione del timer
    void (*activatedManager) (unsigned int, char *) = nullptr;
    // Indica se il timer è attivato o no
    bool activated = true;
    // Indica il numero di aggiornamenti passati dalla ultima attivazione
    unsigned int updates_since = 0;
};


#endif //ARDUWIN_GTIMER_H
