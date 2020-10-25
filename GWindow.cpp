#ifndef GWindow_CPP
#define GWindow_CPP

#include "GWindow.h"
#include <Arduino.h>


GWindow::GWindow() : GArray(){
    strcpy(title , "");
    strcpy(name , "");
    strcpy(tags , "");
    clear();
    // Inizializzo il pulsante di  default
    surf = nullptr;
}

GWindow::GWindow(char n[], char t[]){
    strcpy(title , t);
    strcpy(name , n);
    clear();
    resize(0);
    // Assegno alla superficie di disegno nullptr
    surf = nullptr;
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
    // disabilito il blink
    surf->noBlink();
    // scorro i controlli e li disegno
    for (int x = 0; x < getSize(); x++){
        get(x)->draw();
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

bool GWindow::draw(){
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
        // Imposto il cursore per scrivere il titolo
        surf->setCursor(10 - (strlen(title) / 2) ,0);
        // Scrivo il contenuto
        surf->print(title);
        // Disegno i componenti
        drawControls();
        return true;
    }
    else{
        return false;
    }
}

bool GWindow::redrawControl(int index , int len) {
    // controllo che esista la superficie
    if(surf != nullptr){
        // Controllo che l'indice esista
        if (exists(index, true)) {
            // Esiste
            // Contiene qualcosa
            // Salvo la posizione di inizio
            int start_x = get(index)->getLocation().x;
            int y = get(index)->getLocation().y;
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
                get(index)->draw();
            }
            else{
                #ifdef ENABLE_SERIAL_WARNINGS
                launchWarning(" classe GWindow. Tentativo di ridisegnare un controllo con una dimensione che esce dallo schermo. ");
                launchParam("Finestra", name);
                launchParam("Dimensione", len);
                launchParam("Nome ctrl", get(index)->getName());
                closeLaunch();
                #endif
                return false;
            }
        }
        else{
            #ifdef ENABLE_SERIAL_ERRORS
            launchError(" classe GWindow. Tentativo di ridisegnare un controllo non esistente. ");
            launchParam("Indice", index);
            launchParam("Finestra", name);
            launchParam("Funzione", "redrawControl(int index, int old_size)");
            closeLaunch();
            #endif
            return false;
        }
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GWindow. Tentativo di ridisegnare un controllo senza una superficie impostata. ");
        launchParam("Finestra", name);
        launchParam("Indice ctrl", index);
        launchParam("Funzione", "redrawControl(int index, int old_size)");
        closeLaunch();
        #endif
        return false;
    }
}

bool GWindow::redrawControl(char name[], int old_dim) {
    // Scorro tutti gli elementi
    if (strlen(name) > 0) {
        // La dimensione va bene
        // Scorro tutti gli elementi
        for (int x = 0; x <= getSize(); x++) {
            // controllo che esista
            if(exists(x, true)){
                if (strcmp(get(x)->getName(), name) == 0) {
                    // ridisegno il controllo
                    return redrawControl(x, old_dim);
                }
            }
        }
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GWindow. Tentativo di ridisegnare un controllo senza specificare un nome. ");
        launchParam("Finestra", name);
        launchParam("Dimensione", old_dim);
        closeLaunch();
        #endif
        return false;
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

void GWindow::updateControls(location cursor_pos){
    // Prendo ogni controllo e avvio la ricerca
    back->updateEvents(cursor_pos);
    // Controllo gli eventi dei controlli
    for(int x = 0; x < getSize(); x++){
        if(exists(x, true)){
            get(x)->updateEvents(cursor_pos);
        }
    }
}

#endif
