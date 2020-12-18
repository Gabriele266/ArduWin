#ifndef GWinList_CPP
#define GWinList_CPP
/*
    Autore: cavallo gabriele
    Implementazione della classe gwinlist
*/

#include "GWinList.h"

GWinList::GWinList(){
    clear();
    cursor_pos.x = 0;
    cursor_pos.y = 0;
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
    if(this->exists(index, true)){
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
    if(index != -1){
        // Mostro la finestra
        return draw(index);
    }
	else{
	    return false;
	}
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

GWindow* GWinList::getByName(char *name) {
    // Scorro le finestre
    for(int x = 0; x < getSize(); x++){
        if(strcmp(get(x)->getName(), name) == 0){
            return get(x);
        }
    }
#ifdef ENABLE_SERIAL_WARNINGS
    launchWarning(" classe GWinList. Ricerca finestra per nome non ha restituito nessun risultato. ");
    launchParam("Nome ricerca", name);
    closeLaunch();
#endif
    return nullptr;
}

void GWinList::setCurrentIndex(unsigned int index) {
    // controllo se esiste
    if(exists(index)){
        currentWindow = index;
    }
}

void GWinList::moveCursorUp(){
    // Controllo che non esca dallo schermo
    if((cursor_pos.y - 1) >= 0){
        cursor_pos.y -= 1;
    }
    else{
//        #ifdef ENABLE_SERIAL_ERRORS
//        launchError(" classe GWinList. Tentativo di spostamento del cursore in su in una posizione esterna allo schermo. ");
//        launchParam("Posizione", cursor_pos.y - 1);
//        closeLaunch();
//        #endif
    }
}

void GWinList::moveCursorDown(){
    // Controllo che non esca dallo schermo
    if((cursor_pos.y + 1) <= 3){
        cursor_pos.y += 1;
    }
    else{
//        #ifdef ENABLE_SERIAL_ERRORS
//        launchError(" classe GWinList. Tentativo di spostamento del cursore in giu in una posizione esterna allo schermo. ");
//        launchParam("Posizione", cursor_pos.y + 1);
//        closeLaunch();
//        #endif
    }
}

void GWinList::moveCursorLeft(){
    // Controllo che non esca dallo schermo
    if((cursor_pos.x - 1) >= 0){
        cursor_pos.x -= 1;
    }
    else{
//        #ifdef ENABLE_SERIAL_ERRORS
//        launchError(" classe GWinList. Tentativo di spostamento del cursore verso destra in una posizione esterna allo schermo. ");
//        launchParam("Posizione", cursor_pos.x - 1);
//        closeLaunch();
//        #endif
    }
}

void GWinList::moveCursorRight(){
    // Controllo che non esca dallo schermo
    if((cursor_pos.x + 1) <= 19){
        cursor_pos.x += 1;
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
//        launchError(" classe GWinList. Tentativo di spostamento del cursore verso destra in una posizione esterna allo schermo. ");
//        launchParam("Posizione", cursor_pos.x + 1);
//        closeLaunch();
        #endif
    }
}

void GWinList::resetCursor(){
    cursor_pos.x = 0;
    cursor_pos.y = 0;
}

location GWinList::getCursorPosition(){
    return cursor_pos;
}

#ifdef ARDUWIN_USE_I2C
void GWinList::locateCursor(LiquidCrystal_I2C *surf){
    // controllo che surf non sia nullptr
    if(surf != nullptr){
        // normalizzo la posizione
        normalize(&cursor_pos);
        // La imposto sullo schermo
        surf->setCursor(cursor_pos.x, cursor_pos.y);
        // Attivo il blink
        surf->blink();
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" class GWinList. Tentativo di posizionare il cursore senza uno schermo valido. ");
        launchParam("Lista", __name);
        #endif
    }
}
#else
void GWinList::locateCursor(LiquidCrystal *surf){
    // controllo che surf non sia nullptr
    if(surf != nullptr){
        // normalizzo la posizione
        normalize(&cursor_pos);
        // La imposto sullo schermo
        surf->setCursor(cursor_pos.x, cursor_pos.y);
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" class GWinList. Tentativo di posizionare il cursore senza uno schermo valido. ");
        launchParam("Lista", __name);
        #endif
    }
}
#endif

#ifdef ENABLE_SERIAL_INFO
void GWinList::writeReference() {
    // Scrivo le informazioni sul raccoglitore
    Serial.print(F("Informazioni su GWinList "));
    Serial.println(__name);
    // Scrivo il numero di finestre
    Serial.print(F("Numero di finestre: "));
    Serial.println(getSize());
    // Scrivo il numero massimo di finestre
    Serial.print(F("Numero massimo di finestre: "));
    Serial.println(getMaxSize());
    // Scrivo l'indice della finestra corrente
    Serial.print(F("Indice finestra corrente: "));
    Serial.println(currentWindow);


    // Avvio la scrittura delle informazioni sulle finestre
    for(int x = 0; x < getSize(); x++){
        // Prendo la finestra
        GWindow *win = get(x);
        // Scrivo le informazioni
        Serial.println(F("\n-----------"));
        Serial.print(F("Finestra numero: "));
        Serial.println(x);
        // Controllo se si tratta della finestra corrente
        if(x == currentWindow){
            // Lo scrivo
            Serial.println(F("Finestra corrente. "));
        }

        Serial.print(F("Posizione in memoria: "));
        Serial.println((int) get(x));
        // Controllo se si tratta di un nullptr
        if(win != nullptr){
            // Accedo ai membri interni
            win->writeReference();
        }
    }
}
#endif

#endif