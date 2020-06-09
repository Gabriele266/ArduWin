/*
Autore: Cavallo Gabriele
Rappresenta una checkbox in una interfaccia
*/
#ifndef GCHECKBOX_H
#define GCHECKBOX_H

#include "GButton.h"
#include "GControl.h"
#include "location.h"
#include "GIcon.h"
#include "default_icons.h"

class GCheckBox : public GControl
{
    public:
        /** Default constructor */
        GCheckBox();

        // Costruttore con nome e contenuto e posizione
        GCheckBox(char name[], char cont[], location pos);

        // Costruttore con nome e contenuto
        GCheckBox(char name[], char cont[]);


        // Funzione per checckare il controllo
        void check();

        // Funzione per unchecckare il controllo
        void unCheck();

        // Funzione per ottenere lo stato
        bool isChecked();

        // Funzione per inizializzare il cotrollo
        void begin();

        // Funzione per impostare lo stato
        void setChecked(bool val);
        // Funzione per disegnare il controllo
        bool draw();

        // Funzione per aggiornare gli eventi
        void updateEvents(location l);


    private:
        // Indica lo stato della checkbox
        bool checked = false;

        // Contiene l'icona per lo stato 'checked'
        GIcon *checkedIcon;

        // Contiene l'icona per lo stato 'unchecked'
        GIcon *uncheckedIcon;

};

#endif // GCHECKBOX_H
