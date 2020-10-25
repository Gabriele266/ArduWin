/*
      Autore: Cavallo Gabriele
      Versione: 1.1
      Tipologia licenza:  GPL
      Nome classe: GWindow
      Descrizione classe: Rappresenta una finestra
*/


#ifndef WIN_H
#define WIN_H

#define ARDUWIN_USE_I2C
// Librerie
#include <arduino.h>
#include "GControl.h"
#include "GButton.h"

// Includo la libreria giusta
#if defined ARDUWIN_USE_I2C
// Utilizzo la libreria per gli schermi I2C
#include <LiquidCrystal_I2C.h>
#else
// Utilizzo la libreria standard
#include <LiquidCrystal.h>
#endif

#include "GEvent.h"
#include "location.h"

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

/// Rappresenta una finestra in ArduWin
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
        virtual bool draw();

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
        virtual void updateControls(location cursor_pos);

        /// Ridisegna un controllo pulendo solo la parte di schermo necessaria per la sua visualizzazione e lasciando invariato il resto.
        bool redrawControl(int index, int old_dim);

		/// Ridisegna un controllo pulendo solo la parte di schermo necessaria per la sua visualizzazione e lasciando invariato il resto dato il nome
		bool redrawControl(char name[], int old_dim);

        /// Ottiene il controllo relativo
        GControl* getControl(int ind);

        /// Ottiene il primo controllo con quel nome
        GControl* getControl(char bname[]);

	// Controllo quale libreria è stata inclusa
	#if defined ARDUWIN_USE_I2C
        /// Imposta la superficie su cui disegnare
        void setSurface(LiquidCrystal_I2C *s);
	#else
	void setSurface(LiquidCrystal *s);
	#endif

        /// Disegna solo i controlli della finestra
        void drawControls();

        /// Cancella tutti i controlli
        void clearAll();
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
        // Rappresenta il pulsante indietro
        GButton* back = new GButton();
        // Handler che gestisce il click del pulsante indietro
        void (*clickedBackHandler) (GEvent *event) = nullptr;
        // Puntatore alla surface su cui disegnare
	    #if defined ARDUWIN_USE_I2C
        LiquidCrystal_I2C *surf = nullptr;
	    #else
	    LiquidCrystal *surf = nullptr;
	    #endif

	    // Numero di controlli
        int controls_num = 0;
        // Controlli della finestra
        GControl *controls[20];
        // Definisce se mostrare il pulsante indietro
        bool showBackBtn = false;
};

#endif // WIN_H
