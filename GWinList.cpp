#ifndef GWinList_CPP
#define GWinList_CPP
/*
    Autore: cavallo gabriele
    Implementazione della classe gwinlist
*/

#include "GWinList.h"

GWinList::GWinList(){
    win_num = 0;
    clearWins();
}

GWinList::GWinList(char name[]) : GWinList(){
    strcpy(this->__name, name);
}

void GWinList::setName(char n[]){
    // Imposta il nome
    strcpy(__name , n);
}

char* GWinList::getName(){
    return __name;
}

int GWinList::add(GWindow *win){
    // Aggiungo
    __wins[win_num] = win;
	// Aggiungo una finestra
	win_num++;
    // Restituisco l'indice a cui è stata messa
    return win_num - 1;
}

void GWinList::add(GWindow *win, int index){
    __wins[index] = win;
}

void GWinList::setMain(int ind){
    // Controllo che il valore sia corretto
    if(ind >= 0){
        main_win_index = ind;
    }
    else{
        // Non faccio niente
    }
}

void GWinList::addMain(GWindow *win){
    main_win_index = add(win);
}

int GWinList::getMainInd(){
    return main_win_index;
}

void GWinList::clearWins(){
    for(int x = 0; x < 10; x ++){
        __wins[x] = nullptr;
    }
}

void GWinList::remove(int ind){
	// Controllo l'indice
	// Controllo se esiste e se e' legato ad un controllo
	if (ind >= 0 && ind < win_num) {
        // Controllo che l'indice dato non sia anche la finestra corrente
        if (currentWindow == ind) {
            // Svuoto la variabile
            currentWindow = 0;
        }
        // Procedo con il resto

		// Controllo se e' l'ultimo dell' array
		if (ind == win_num - 1) {
			// E' l'ultimo
			// Non effettuo alcun flush degli elementi
			// Svuoto il puntatore e decremento il contatore dei controlli
			__wins[ind] = nullptr;

			win_num--;
		}
		else {
			// L'elemento non e' l'ultimo
			// Eseguo il flush degli elementi
			// Parto da quello successivo a ind
			// Sposto tutti gli altri di 1 posizione indietro e infine decremento il contatore dei controlli
			for (int index = ind + 1; index < win_num; index++) {
				__wins[index - 1] = __wins[index];
			}
			// Decremento
			win_num--;
		}

	}
}

GWindow* GWinList::get(int ind){
    // Controllo che l'indice dato esista
	if (ind >= 0 && ind <= win_num) {
        // L'indice esiste
        // Restituisco un puntatore alla finestra
		return __wins[ind];
	}
}

bool GWinList::draw(int index){
    // Controllo che l'indice dato esista
    if(index >= 0 && index < win_num){
        // Controllo che la finestra non sia un puntatore nullo
		if(__wins[index] != nullptr){
            // Disegno la finestra
			__wins[index]->draw();
			// Imposto la finestra corrente come finestra corrente
			currentWindow = index;
			return true;
		}
		else{
            return false;
		}
    }
    else{
        return false;
    }
}

bool GWinList::isCurrent(char name[]) {
	// Calcolo il nome della finestra corrente
	// Controllo
	if (strcmp(__wins[currentWindow]->getName(), name) == 0) {
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
	// Salvo l'indice come finestra  principale
	currentWindow = index;
}

int GWinList::resolveIndex(char __name[]) {
	for (int cur = 0; cur < win_num; cur++) {
		// Controllo che la finestra esista
		if (__wins[cur] != nullptr) {
			// Confronto
			if (strcmp(__wins[cur]->getName(), __name) == 0) {
				// Le due stringhe sono uguali
				// Disegno la finestra
                return cur;
			}
		}
		else{

		}
	}
	return -1;
}

void GWinList::setCurrentIndex(unsigned int index) {
    // controllo se esiste
    if(index >= 0 && index < win_num){
        currentWindow = index;
    }
}

#endif
