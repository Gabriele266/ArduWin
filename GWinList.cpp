#ifndef GWinList_CPP
#define GWinList_CPP
/*
    Autore: cavallo gabriele
    Implementazione della classe gwinlist
*/

#include "GWinList.h"

GWinList::GWinList(){
    clear();
}

GWinList::GWinList(char name[]) : GWinList(){
    strcpy(__name, name);
}

void GWinList::setName(char n[]){
    // Imposta il nome
    strcpy(__name , n);
}

char* GWinList::getName(){
    return __name;
}

void GWinList::setMain(int ind){
    // Controllo che il valore sia corretto
    if(ind >= 0){
        main_win_index = ind;
    }
    else{
        #ifdef ENABLE_SERIAL_WARNINGS
        launchWarning(" classe GWinList. Tentativo di impostare l'indice finestra main con un valore non esistente. ");
        launchParam("Indice", ind);
        launchParam("Nome lista", __name);
        closeLaunch();
        #endif
    }
}

void GWinList::addMain(GWindow *win){
    main_win_index = add(win);
}

int GWinList::getMainInd(){
    return main_win_index;
}

bool GWinList::draw(int index){
    // controllo se esiste
    if(exists(index)){
        // Disegno la finestra
        get(index)->draw();
        // Salvo l'indice corrente
        currentWindow = index;
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GWinList. Tentativo di disegnare una finestra nulla o non esistente. ");
        launchParam("Indice", index);
        launchParam("Nome lista", __name);
        closeLaunch();
        #endif
    }
}

bool GWinList::isCurrent(char name[]) {
	// Calcolo il nome della finestra corrente
	// Controllo
	if (strcmp(get(currentWindow)->getName(), name) == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool GWinList::drawCurrent(){
   return draw(currentWindow);
}

int GWinList::getIndex(char name[]){
	return resolveIndex(name);
}

bool GWinList::draw(char name[]){
    // Risolvo il nome della finestra in un indice e mostro il tutto
	int index = 0;
	// Calcolo l'indice
	index = resolveIndex(name);

	// Mostro la finestra
	return draw(index);
}

bool GWinList::drawMain(){
    // Mostro la finestra principale
    return draw(main_win_index);
}

void GWinList::setMain(char name[]) {
	// Risolvo l'indice
	int index = resolveIndex(name);
}

int GWinList::resolveIndex(char _name[]) {
	for (int cur = 0; cur < getSize(); cur++) {
		// Controllo che la finestra esista
		if (exists((nat) cur)) {
			// Confronto
			if (strcmp(get(cur)->getName(), _name) == 0) {
				// Le due stringhe sono uguali
				// Disegno la finestra
                return cur;
			}
		}
		else{
            #ifdef ENABLE_SERIAL_ERRORS
            launchError(" classe GWinList. Ricerca finestra tramite nome ha trovato un elemento nullo. ");
            launchParam("Nome lista", __name);
            launchParam("Ricerca", _name);
            closeLaunch();
            #endif
		}
	}
    #ifdef ENABLE_SERIAL_WARNINGS
    launchWarning(" classe GWinList. Ricerca finestra tramite nome non ha restituito nessun risultato. ");
    launchParam("Nome", _name);
    launchParam("Nome lista", __name);
    closeLaunch();
    #endif
	return -1;
}

void GWinList::setCurrentIndex(unsigned int index) {
    // controllo se esiste
    if(exists(index)){
        currentWindow = index;
    }
}

#endif