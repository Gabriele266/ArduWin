/*
Autore: Gabriele Cavallo
Versione: 1.1
Classe che rappresenta una notifica in ambiente ArduWin
*/

#ifndef GNOTIFICATION_H
#define GNOTIFICATION_H

// Header di arduino
#include <Arduino.h>
// Header per lo schermo
#include <LiquidCrystal_I2C.h>

class GNotification
{
    public:
        /// Costruttore di base
        GNotification();
        /// Costruttore che definisce testo e titolo della notifica
        GNotification(char title[], char text[]);
        /// Costruttore che definisce testo, titolo e superficie
        GNotification(char title[], char text[], LiquidCrystal_I2C *surf);

        /// Imposta il testo della notifica
        void setText(char text[]);

        /// Restituisce il testo della notifica
        char* getText();

        /// Imposta il titolo
        void setTitle(char t[]);
        char* getTitle();

        /// Imposta la superficie
        void setSurface(LiquidCrystal_I2C *surf);
        /// Restituisce un puntatore alla superficie
        LiquidCrystal_I2C* getSurface();

        /// Disegna la notifica
        virtual bool draw();

        /// Aggiorna la notifica
        virtual bool update(unsigned int x, unsigned int y);

        /// Imposta il gestore degli eventi
        void setHandler(void (*ha)(void));

    protected:
    private:
        // Puntatore alla superficie su cui disegnare
        LiquidCrystal_I2C *surf;
        // Testo membro della notifica
        char text[30];
        // Titolo della notifica
        char title[30];
        // Gestore della notifica
        void (*handle)();
        // Determina se la notifica e' stata accettata dall' utente
        bool accepted;
};

#endif // GNOTIFICATION_H
