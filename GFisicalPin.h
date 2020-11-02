//
// Created by Gabriele on 31/10/2020.
// Rappresenta un pin in ambiente arduwin
// fornisce funzione per la gestione del pin, conversione di tipi

#ifndef ARDUWIN_GFISICALPIN_H
#define ARDUWIN_GFISICALPIN_H

// Header di arduino
#include <Arduino.h>
// Header modalità di esecuzione
#include "flags.cpp"

/// Rappresenta un numero naturale
typedef unsigned short int nat;

/// Rappresenta il metodo di utilizzo del pin
enum PinUseMode{
    OutputMode,
    InputMode,
    NoMode
};

/// Rappresenta la tipologia di onda da generare sul pin
enum PinWaveMode{
    NormalWave,         /// Genera una onda con intensità costante
    PwmWave,            /// Genera una onda quadra per simulare una analogica
    SinusoidalWave,      /// Genera una onda sinusoidale (pin analogici)
    NoWave
};

/// Rappresenta il tipo di pin
enum PinType{
    Digital,
    Pwm,
    Analog,
    Builtin
};

/// Rappresenta un pin in ambiente ArduWin
class GFisicalPin {
public:
    /// Costruttore di default
    GFisicalPin();
    /// Costruttore che imposta anche il nome
    GFisicalPin(char name[]);
    /// Costruttore con nome e numero per il pin
    GFisicalPin(char name[], nat number);
    /// Costruttore con nome, numero del pin, tipologia di pin, modalità di accesso e tipologia di onda generata
    GFisicalPin(char name[], nat number, PinType type, PinUseMode mode, PinWaveMode wave);

    /// Imposta il numero del pin e risale alla tipologia dello stesso
    void setNumber(int number);
    /// Restituisce il numero del pin
    int getNumber();

    /// Imposta il nome del pin
    void setName(char name[]);
    /// Restituisce il nome del pin
    char* getName();

    /// Forza l'inpostazione della tipologia di pin
    void setType(PinType type);
    /// Restituisce il tipo di pin in uso
    PinType getType();

    /// Scrive sul pin generando l'onda desiderata
    void writeWave(PinWaveMode mode, nat value = HIGH);

    /// Inverte lo stato del pin
    void invertValue();

    /// Inizializza il pin seguendo le impostazioni date
    bool begin();

    /// Determina se sulla scheda esiste un pin con quel numero
    static bool exists(nat pin);
private:
    // Numero del pin
    nat pin;
    // Tipologia di accesso
    PinUseMode use_mode = PinUseMode::NoMode;
    // Stato del pin
    PinType type = 0;
    // Applied wave type
    PinWaveMode mode;
    // Nome assegnato al pin
    char name[15];
    // Valore dell' ultima operazione di scrittura su pin
    nat last_write_value = 0;
};


#endif //ARDUWIN_GFISICALPIN_H
