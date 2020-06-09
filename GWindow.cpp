#ifndef GWindow_CPP
#define GWindow_CPP

#include "GWindow.h"
#include <Arduino.h>


GWindow::GWindow(){
    strcpy(title , "");
    strcpy(name , "");
    strcpy(tags , "");
    controls_num = 0;
    // Inizializzo il pulsante di  default

}

GWindow::GWindow(char n[], char t[]){
    strcpy(title , t);
    strcpy(name , n);
    controls_num = 0;
}

void GWindow::setTitle(char t[]){
    // Imposto il titolo solo se non è vuoto
    strcpy(title, t);
}


char* GWindow::getTitle(){
    return title;
}

void GWindow::setName(char n[]){
    // Imposto il nome solo se non è nullo
    strcpy(name, n);
}
void GWindow::drawControls(){
    surf->noBlink();
    for (int x = 0; x < controls_num; x++){
        controls[x]->draw();
    }
}
char* GWindow::getName(){
    return name;
}

void GWindow::setTags(char t[]){
    strcpy(tags, t);
}

void GWindow::addTag(char t[]){
    // Aggiungo il tag controllando di non incappare in errori
    strcat(tags, t);
}

void GWindow::setShowBackBtn(bool val){
    showBackBtn = val;
}

bool GWindow::isBackBtnShowable(){
    return showBackBtn;
}
char* GWindow::getTags(){
    return tags;
}

void GWindow::setBackBtnPos(BackBtnPos p){
    pos = p;
}

BackBtnPos GWindow::getBackBtnPos(){
    return pos;
}

void GWindow::setBackBtnHandle(void (*btnHandler)(GEvent *event)){
    clickedBackHandler = btnHandler;
}

void GWindow::setBackBtnType(BackBtnType t) {
    type = t;
}

BackBtnType GWindow::getBackBtnType() {
    return type;
}

void GWindow::draw(){
    // Disegna la finestra

    // Controllo che la superficie esista
    if (surf != nullptr) {
        // Pulisco lo schermo
        surf->clear();
        // Disegno il pulsante indietro
        if (showBackBtn) {
            // Controllo la posizione immessa dall' utente
            switch ((int)pos) {
            case BackBtnPos::TopCenter:
                // Metto il pulsante al centro
                back->setLocation(createLocation(7, 1));
                break;
            case BackBtnPos::TopLeft:
                back->setLocation(createLocation(0, 0));
                break;
            case BackBtnPos::TopRight:
                back->setLocation(createLocation(16, 0));
                break;
            case BackBtnPos::BottomLeft:
                back->setLocation(createLocation(0, 3));
				break;
			case BackBtnPos::BottomRight:
                back->setLocation(createLocation(17, 3));
				break;
			case BackBtnPos::BottomCenter:
                back->setLocation(createLocation(7, 3));
				break;
            default:

                break;
            };
            // Controllo la dimensione scelta e formatto la stringa
            switch ((int)type) {
            case BackBtnType::Small:
                back->setText("<");
                break;
            case BackBtnType::Medium:
                back->setText("<-");
                break;
            case BackBtnType::Large:
                back->setText("<--");
                break;
            };
            back->setIcon(nullptr);
            back->setEventHandler(clickedBackHandler);
            back->enable();
            // Disegno il pulsante
            back->draw();
        }
    }
    // Imposto il cursore per scrivere il titolo
    surf->setCursor(10 - (strlen(title) / 2) ,0);
    // Scrivo il contenuto
    surf->print(title);
    // Disegno i componenti
    drawControls();
}

void GWindow::redrawControl(int index , int len) {
    // Controllo che l'indice esista
    if (index >= 0 && index < controls_num) {
        // Esiste
        // Controllo che il conotrollo relativo non sia nullo
        if (controls[index] != nullptr) {
            // Contiene qualcosa
            // Salvo la posizione di inizio
            int start_x = controls[index]->getLocation().x;
            int y = controls[index]->getLocation().y;
            // Controllo che non vada fuori dallo schermo
            if (len + start_x <= 19) {
                // Va bene posso cancellare
				// Pulisco lo spazio
				for (int x = start_x; x <= len + start_x; x++) {
					// Imposto la posizione
					surf->setCursor(x, y);
					// Scrivo un carattere vuoto
					surf->print(" ");
				}
				// Disegno il controllo
				controls[index]->draw();
            }
        }
    }
}

void GWindow::redrawControl(char name[], int old_dim) {
    // Scorro tutti gli elementi
    if (strlen(name) > 0) {
        // La dimensione va bene
        // Scorro tutti gli elementi
        for (int x = 0; x <= controls_num; x++) {
            if (strcmp(controls[x]->getName(), name) == 0) {
                redrawControl(x, old_dim);
                break;
            }
        }
    }
}

#if defined ARDUWIN_USE_I2C
void GWindow::setSurface(LiquidCrystal_I2C *s){
    surf = s;
    back->setSurface(s);
}
#else
void GWindow::setSurface(LiquidCrystal *s){
    surf = s;
    back->setSurface(s);
}
#endif

int GWindow::addControl(GControl *l){
    controls[controls_num] = l;
    controls_num++;
    return controls_num;
}

void GWindow::removeControl(int ind){
    // Controllo l'indice
    // Controllo se esiste e se e' legato ad un controllo
    if(ind >= 0 && ind < controls_num){
        // Controllo se e' l'ultimo dell' array
        if (ind == controls_num - 1) {
            // E' l'ultimo
            // Non effettuo alcun flush degli elementi
            // Svuoto il puntatore e decremento il contatore dei controlli
            controls[ind] = nullptr;
            controls_num--;
        }
        else {
            // L'elemento non e' l'ultimo
            // Eseguo il flush degli elementi
            // Parto da quello successivo a ind
            // Sposto tutti gli altri di 1 posizione indietro e infine decremento il contatore dei controlli
            for (int index = ind + 1; index < controls_num; index++) {
                controls[index - 1] = controls[index];
            }
            // Decremento
            controls_num--;
        }
    }
}

void GWindow::removeControl(char bname[]) {
    // Cerco il controllo che ha quel nome
    // NOTA: si ferma al primo risultato
    for (int index = 0; index < controls_num; index++) {
        // Controllo che il controllo corrente esista
        if (controls[index] != nullptr) {
            if (strcmp(controls[index]->getName(), bname) == 0) {
                // Trovato il controllo con quel nome
                // Chiamo la funzione per rimuoverlo
                removeControl(index);
                break;
            }
        }
    }
}

GControl* GWindow::getControl(int index) {
    // Controllo l'indice
    if (index >= 0 && index < controls_num) {
        return controls[index];
    }
}

GControl* GWindow::getControl(char bname[]) {
    // Controllo che il nome non sia nullo
    if (strlen(bname) > 0) {
        // Procedo
		for (int index = 0; index < controls_num; index++) {
			// Controllo che il controllo corrente esista
			if (controls[index] != nullptr) {
				if (strcmp(controls[index]->getName(), bname) == 0) {
					// Trovato il controllo con quel nome
					// Chiamo la funzione per rimuoverlo
					return controls[index];
				}
			}
		}
    }
}

void GWindow::updateControls(location cursor_pos){
    // Prendo ogni controllo e avvio la ricerca
    back->updateEvents(cursor_pos);
    // Controllo gli eventi dei controlli
    for(int x = 0; x < controls_num; x++){
        controls[x]->updateEvents(cursor_pos);
    }
}

#endif
