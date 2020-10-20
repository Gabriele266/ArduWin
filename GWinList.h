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

class GWinList{
      public:
            GWinList();
            GWinList(char name[]);

            // Ottiene o imposta il nome
            void setName(char n[]);
            char* getName();

            // Aggiunge una finestra alla raccolta
            int add(GWindow* w);
            // Aggiunge la finestra nell' indice specifico
            void add(GWindow *w, int index);

            // Imposta la finestra principale tramite un indice numerico
            void setMain(int ind);
            void setMain(char name[]);

            int getMainInd();

            // Rimuove una finestra dal raccoglitore
            void remove(int ind);

            // Ottiene una finestra a partire da un indice
            GWindow* get(int ind);
            // Ottiene una finestra a partire da un nome
            GWindow* get(char bname[]);

			// Ottiene l'indice di una finestra con quel nome
			int getIndex(char name[]);

            // Mostra una finestra
            void draw(int ind);

            // Mostra la finestra principale
            void drawMain();

            // Mostra una finestra a partire dal nome
            void draw(char name[]);

			// Mostra la finestra impostata come corrente
			void drawCurrent();
			int getCurrent() {return currentWindow;}

            /// Determina se la finestra indicata dal nome è la finestra corrente
			bool isCurrent(char name[]);
      private:
          // Numero di finestre
          int win_num = 0;
          // Nome della lista
          char __name[20];
          // Indice della finestra principale
          int main_win_index = 0;
	      // Array di finestre
          GWindow *__wins[10];
		  // Indice della finestra corrente
		  int currentWindow;
          // Funzione per ottenere l'indice di una finestra a partire dal nome
          int resolveIndex(char name[]);
};

#endif // WINLIST_H

