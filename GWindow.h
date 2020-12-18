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

// Header per gli eventi
#include "GEvent.h"
// Header per le posizioni
#include "location.h"
// Header per gli array
#include "GArray.h"
// Header per gestione errori
#include "flags.cpp"

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
class GWindow : public GArray<GControl, 15>{
    public:
        /// Costruttore di default
        GWindow();

        /// Costruttore che imposta titolo e nome della finestra
        GWindow(char name[], char title[]);

        /// Imposta il titolo
        void setTitle(char t[]);

        /// Restituisce il titolo
        char* getTitle();

        /// Ottiene o imposta il nome
        void setName(char n[]);

        /// Restituisce il nome della finestra
        char* getName();

        /// Imposta la posizione del pulsante indietro
        void setBackBtnPos(BackBtnPos p);

        /// Restituisce la posizione del pulsante indietro
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

        /// Imposta se mostrare o no il pulsante indietro
        void setShowBackBtn(bool val);

        /// Ottiene un valore booleano che indica se mostrare il pulsante indietro
        bool isBackBtnShowable();

        /// Effettua il controllo degli eventi di click relativi a tutti i controlli
        virtual void updateControls(location cursor_pos);

        /// Ridisegna un controllo pulendo solo la parte di schermo necessaria per la sua visualizzazione e lasciando invariato il resto.
        bool redrawControl(int index, int old_dim);

		/// Ridisegna un controllo pulendo solo la parte di schermo necessaria per la sua visualizzazione e lasciando invariato il resto dato il nome
		bool redrawControl(char name[], int old_dim);

		/// Imposta la funzione da chiamare quando la finestra viene disegnata
		void setOnDrawFunction(void (*func)(GEvent *event));

	    // a seconda della tipologia di libreria da utilizzare
	    #if defined ARDUWIN_USE_I2C
            /// Imposta la superficie su cui disegnare
            void setSurface(LiquidCrystal_I2C *s);
	    #else
	        void setSurface(LiquidCrystal *s);
	    #endif

        #ifdef ENABLE_SERIAL_INFO
	        /// Mostra le informazioni relative alla interfaccia
	        void writeReference();
        #endif

        /// Disegna solo i controlli della finestra
        void drawControls();

    private:
        // Nome della finestra
		char name[15];
		// Titolo della finestra
		char title[20];

        // Posizione del pulsante indietro
        BackBtnPos pos;
        // Tipologia del pulsante indietro
        BackBtnType type;
        // Rappresenta il pulsante indietro
        GButton* back = new GButton();

        // Handler che gestisce il click del pulsante indietro
        void (*clickedBackHandler) (GEvent *event) = nullptr;
        // Handler chiamato dopo il disegno della finestra
        void (*windowDrawn)(GEvent *event) = nullptr;

        // Puntatore alla surface su cui disegnare
	    #if defined ARDUWIN_USE_I2C
        LiquidCrystal_I2C *surf = nullptr;
	    #else
	    LiquidCrystal *surf = nullptr;
	    #endif
        // Definisce se mostrare il pulsante indietro
        bool showBackBtn = false;
};
#endif // WIN_H
