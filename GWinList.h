/*
      Autore: Cavallo Gabriele
      Versione: 1.1
      Tipologia licenza: GPL
      Descrizione licenza: GPL
      Nome classe: GWinList
      Rappresenta una lista di finestre gestite.
*/

#ifndef WINLIST_H
#define WINLIST_H
#pragma once
// Librerie
#include <Arduino.h>
#include "GWindow.h"
#include "flags.cpp"
#include "GArray.h"

#define ARDUWIN_USE_I2C

#ifdef ARDUWIN_USE_I2C
#include <LiquidCrystal_I2C.h>
#else
#include <LiquidCrystal.h>
#endif

/// Rappresenta una lista di finestre in ambiente ArduWin
class GWinList : public GArray<GWindow, 10>{
      public:
            GWinList();

            /// Imposta la finestra principale tramite un indice numerico
            void setMain(int ind);

            void setMain(char name[]);

            /// Imposta l'indice della finestra corrente
            void setCurrentIndex(unsigned int index);

            /// Aggiunge la finestra alla lista e la imposta come principale
            void addMain(GWindow *win);

            /// Restituisce l'indice della finestra principale
            int getMainInd();

            /// Rimuove una finestra dal raccoglitore
            void remove(int ind);

			/// Ottiene l'indice di una finestra con quel nome
			int getIndex(char name[]);

            /// Mostra una finestra
            bool draw(int ind);

            /// Mostra la finestra principale
            bool drawMain();

            /// Mostra una finestra a partire dal nome
            bool draw(char name[]);

			/// Mostra la finestra impostata come corrente
			bool drawCurrent();

			/// Restituisce la finestra corrente
			int getCurrent() {return currentWindow;}

            /// Determina se la finestra indicata dal nome � la finestra corrente
			bool isCurrent(char name[]);

            /// Sposta il cursore a sinistra
            void moveCursorLeft();

            /// Muove il cursore a destra
            void moveCursorRight();

            /// Muove il cursore in su
            void moveCursorUp();

            /// Muove il cursore in giu
            void moveCursorDown();

            /// Riporta il cursore alla posizione home (0,0)
            void resetCursor();

            /// Posiziona il cursore in una posizione ben definita
            void moveCursor(location pos);

            /// Restituisce la posizione del cursore nello schermo
            location getCursorPosition();

            /// Funzioni per posizionare il cursore nello schermo
            #ifdef ARDUWIN_USE_I2C
            void locateCursor(LiquidCrystal_I2C *surf);
            #else
            void locateCursor(LiquidCrystal *surf);
            #endif

            /// Restituisce la prima finestra con quel nome
            GWindow* getByName(char name[]);

#ifdef ENABLE_SERIAL_INFO
            /// Mostra le informazioni sul raccoglitore di finestre
            void writeReference();
#endif
      private:
          // Indice della finestra principale
          int main_win_index = -1;
		  // Indice della finestra corrente
		  int currentWindow = 0;
          // Funzione per ottenere l'indice di una finestra a partire dal nome
          int resolveIndex(char name[]);
          // Posizione del cursore
          location cursor_pos;
};

#endif // WINLIST_H
