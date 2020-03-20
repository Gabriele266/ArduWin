#ifndef GEvent_H
#define GEvent_H

/*
    Autore: Cavallo Gabriele
    Versione: 1.1
    Descrizione: Rappresenta un GEvento nella libreria arducore
*/
#include <Arduino.h>
#include "Location.h"


class GEvent
{
    public:
        /** Default constructor */
        GEvent();
        /** Default destructor */
        virtual ~GEvent();

        /// Imposta il nome dell' GEvento
        void setName(char name[]);
        /// Ottiene il nome dell' GEvento
        char* getName();

        /// Imposta la posizione a cui è avvenuto
        void setPosition(location l);
        /// Ottiene la posizione a cui è avvenuto
        location getPosition();

        /// Imposta il sender dell' Evento
        void setSender(char sen[]);
        char* getSender();

        /// Avvia la gestione dell' Evento
        virtual void throwEvent();

        /// Determina se l'GEvento è stato gestito da qualcuno
        bool isThrown();

    protected:

    private:

        /// Nome dell' GEvento
        char name[60];
        /// Posizione dell' GEvento
        location position;
        /// Inviatore dell' GEvento
        char sender[60];
        /// Determina se è stato gestito
        bool thrown = false;


};

#endif // GEvent_H
