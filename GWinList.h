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

/// Rappresenta una lista di finestre in ambiente ArduWin
class GWinList : public GArray<GWindow, 10>{
      public:
            GWinList();
            GWinList(char name[]);

            /// Ottiene o imposta il nome
            void setName(char n[]);
            char* getName();

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

      private:
          // Indice della finestra principale
          int main_win_index = 0;
		  // Indice della finestra corrente
		  int currentWindow;
          // Funzione per ottenere l'indice di una finestra a partire dal nome
          int resolveIndex(char name[]);
          // Nome della lista
          char __name[20];
};

#endif // WINLIST_H
