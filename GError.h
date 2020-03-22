#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>

/// Rappresenta un livello di gravita' dell' errore
enum ErrorLevel{
    Information = 0,
    Low,
    MediumL,
    High,
    Fatal
};

/// Rappresenta un errore nell' ambiente ArduCore
class GError
{
    public:
        /** Default constructor */
        GError();
        GError
        (char send[], char name[]);

        /// Imposta il nome dell' errore
        void setName(char name[]);
        /// Ottiene il nome dell' errore
        char* getName();
        /// Imposta il sender
        void setSender(char send[]);
        /// Ottiene il sender
        char* getSender();
        /// Imposta il numero di volte che e' successo
        void setTimes(unsigned int val);
        /// Ottiene il numenro di volte che e' successo
        unsigned int getTimes();
        /// Incrementa il numero di successi
        void increaseTimes();
        /// Gestisce l'errore
        void throw_error();

        /// Imposta l'header
        void setHeader(char head[]);
        /// Ottiene l'header
        char* getHeader();

        /// Imposta il livello
        void setLevel(ErrorLevel e);
        /// Ottiene il livello
        ErrorLevel getLevel();

    private:
        // Nome assegnato ad un errore
        char name[30];
        // Numero di volte che si e' verificato
        int times = 0;
        // Oggetto che ha inviato l'errore
        char sender[20];
        // Definisce se e' stato gestito
        bool thrown = false;
        // Intestazione dell' errore
        char header[30];
        // Gravità errore
        ErrorLevel level;
};

#endif // ERROR_H

