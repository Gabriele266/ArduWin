/*classe generata dal programma CodeUtils di Gabriele Cavallo.
La seguente classe contiene un costruttore.
      Autore: Cavallo Gabriele
      Versione: 1.1
      Tipologia licenza:  Freeware
      Descrizione licenza: Non Open source, è illegale modificare il codice
      Nome classe: GWindow
      Descrizione classe: Rappresenta una finestra all' interno delle mie api
      Progetto: SvegliaArduino

	  Il seguente file è parte del progetto Sveglia Arduino
*/


#ifndef WIN_H
#define WIN_H

// Librerie
#include <arduino.h>
#include "GControl.h"
#include "LiquidCrystal_I2C/LiquidCrystal_I2C.h"
#include "GEvent.h"
#include "Location.h"

// Enumerazione per i tipi di pulsante indietro
enum BackBtnType : int{
    Small = 0,
    Medium,
    Large
};

// Enumerazione che definisce la posizione del pulsante indietro
enum BackBtnPos : int{
    TopCenter = 0,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

class GWindow{

    public:
        /// Costruttore di default
        GWindow();
        /// Costruttore che imposta titolo e nome della finestra
        GWindow(char name[], char title[]);

        /// Imposta o ottiene il titolo
        void setTitle(char t[]);
        char* getTitle();
        /// Ottiene o imposta il nome
        void setName(char n[]);
        char* getName();

        /// Ottiene o imposta i tag
        void setTags(char t[]);
        void addTag(char t[]);
        char* getTags();

        /// Ottiene o imposta la posizione del pulsante indietro
        void setBackBtnPos(BackBtnPos p);
        BackBtnPos getBackBtnPos();

        /// Imposta la dimensione del pulsante indietro
        void setBackBtnType(BackBtnType t);
        /// Restituisce la tipologia del pulsante indietro
        BackBtnType getBackBtnType();

        /// Imposta l'handler per il click
        void setBackBtnHandle(
                              void(*backHandler)(GEvent *event));
        /// Disegna la finestra partendo dal titolo e poi chiama le funzioni di draw dei componenti figlio
        void draw();

        /// Aggiunge un controllo alla lista
        int addControl(GControl *l);

        /// Imposta se mostrare o no il pulsante indietro
        void setShowBackBtn(bool val);
        /// Ottiene un valore booleano che indica se mostrare il pulsante indietro
        bool isBackBtnShowable();

        /// Rimuove un controllo
        void removeControl(int ind);
        void removeControl(char bname[]);

        /// Effettua il controllo degli eventi di click relativi a tutti i controlli
        void updateControls(location cursor_pos);

        /// Ottiene il controllo relativo
        GControl* getControl(int ind);
        /// Ottiene il primo controllo con quel nome
        GControl* getControl(char bname[]);

        /// Imposta la superficie su cui disegnare
        void setSurface(LiquidCrystal_I2C *s);
        /// Disegna solo i controlli della finestra
        void drawControls();

    private:
        // Nome della finestra
		char name[20];
		// Titolo della finestra
		char title[20];
		// Tags relativi alla finestra
		char tags[30];

        // Posizione del pulsante indietro
        BackBtnPos pos;
        // Tipologia del pulsante indietro
        BackBtnType type;
        // Handler che gestisce il click del pulsante indietro
        void (*clickedBackHandler) (GEvent *event) = nullptr;
        // Puntatore alla surface su cui disegnare
        LiquidCrystal_I2C *surf;
        // Numero di controlli
        int controls_num = 0;
        GControl *controls[20];
        // Definisce se mostrare il pulsante indietro
        bool showBackBtn = false;
};





#endif // WIN_H
