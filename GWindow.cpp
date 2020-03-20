#ifndef GWindow_CPP
#define GWindow_CPP

#include "GWindow.h"
#include <Arduino.h>
#include <MemoryFree.h>

/*
=============================================
Il seguente file è parte del progetto sveglia arduino
=============================================
*/

GWindow::GWindow(){
    strcpy(title , "");
    strcpy(name , "");
    strcpy(tags , "");
    controls_num = 0;
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
            // Stringa che contiene la formattazione in testo del pulsante indietro
            char back_form[4];
            // Controllo la posizione immessa dall' utente
            switch ((int)pos) {
            case BackBtnPos::TopCenter:
                // Metto il pulsante al centro
                surf->setCursor(7, 0);
                break;
            case BackBtnPos::TopLeft:
                surf->setCursor(0, 0);
                break;
            case BackBtnPos::TopRight:
                surf->setCursor(17, 0);
                break;
                case BackBtnPos::BottomLeft:
                    surf->setCursor(0, 3);
                    break;
                case BackBtnPos::BottomRight:
                    surf->setCursor(19, 3);
                    break;
                case BackBtnPos::BottomCenter:
                    surf->setCursor(7, 3);
                    break;
            default:
                    
                break;
            };
            // Controllo la dimensione scelta e formatto la stringa
            switch ((int)type) {
            case BackBtnType::Small:
                strcpy(back_form, "<");
                break;
            case BackBtnType::Medium:
                strcpy(back_form, "<-");
                break;
            case BackBtnType::Large:
                strcpy(back_form, "<--");
                break;
            };
            // Disegno il pulsante
			surf->print(back_form);
        }
    }
    // Imposto il cursore per scrivere il titolo
    surf->setCursor(10 - (strlen(title) / 2) ,0);
    // Scrivo il contenuto
    surf->print(title);
    // Disegno i componenti
    drawControls();
}

void GWindow::setSurface(LiquidCrystal_I2C *s){
    surf = s;
}

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
    if(cursor_pos.x >= 0 && cursor_pos.x <= 3 && cursor_pos.y == 0){
            // Si trova nella area del pulsante indietro
        if(clickedBackHandler != nullptr){
            // Controllo di non incappare in errori
            // Creo un nuovo evento
            GEvent *event = new GEvent();
            // Imposto il nome
            event->setName("backHandlerClick");
            // Imposto il sender
            event->setSender(this->getName());
            // Imposto la posizione
            event->setPosition(createLocation());
            // Avvio l'handler
            clickedBackHandler(event);
        }
    }
    // Controllo gli eventi dei controlli
    for(int x = 1; x < controls_num; x++){
        controls[x]->updateEvents(cursor_pos);
    }
}

#endif
