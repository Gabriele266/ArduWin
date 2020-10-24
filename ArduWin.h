/*
========================================================
========================================================
File principale del Framework ArduWin
Questo framework serve per gestire l'interfaccia visiva su schermi lcd di arduino
Licenza: GPL
La licenza è valida su tutti i sorgenti del progetto.
========================================================
========================================================
*/
#ifndef ARDUWIN_HEAD
#define ARDUWIN_HEAD

// Espone la versione del framework
#define ARDUWIN_VERSION 2.1

// HEADER PER LE FINESTRE
#include "GWindow.h"
// HEADER PER LE LISTE DI FINESTRE
#include "GWinList.h"
// HEADER PER I CONTROLLI
#include "GControl.h"
// Header per le etichette
#include "GLabel.h"
// Header per itipi di dato
#include "location.h"
// Header per i pulsanti
#include "GButton.h"
// Header per gli eventi
#include "GEvent.h"
// Header per le icone
#include "GIcon.h"
// Header con le icone predefinite
#include "default_icons.h"
// Header per il checkbox
#include "GCheckBox.h"
// Header per le notifiche
#include "GNotification.h"
// Header per gli errori
#include "GError.h"
// Header per gli array
#include "GArray.h"

/// Determina se la versione è migliore o peggiore
static bool greaterThan(float version){
      if(ARDUWIN_VERSION > version){
            return true;
      }
      return false;
}

#endif // ARDUWIN_HEAD

