/*
 * Autore: Cavallo Gabriele
 * Esempio basic_label_with_icon
 * Crea una finestra con un titolo, crea una etichetta e gli assegna una icona
 * Aggiunge l'etichetta alla finestra e mostra tutto
 */
 
// Header di ArduCore
#include <ArduWin.h>
// Header per gli schermi lcd i2c
#include <LiquidCrystal_I2C.h>

// Finestra dell' esempio
GWindow *win = new GWindow("win", "Finestra");

// Etichetta che conterrà un icona e del testo: lab
GLabel *lab = new GLabel("lab", "lab");

// Icona da aggiungere alla etichetta
GIcon *icn = new GIcon();

// Rappresenta il display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Inizializzo lo schermo
  lcd.init();
  lcd.backlight();
  // Pulisco lo schermo
  lcd.clear();

  // Imposto la superficie da usare per disegnare la finestra
  win->setSurface(&lcd);

  // Inizializzo l'icona
  // Imposto il codice (utilizzo l'icona predefinita clock_icon. Si trova in icons/clock_icon.cpp
  icn->setCode(clock_icon);
  // Imposto l'indice per l'icona
  icn->setIndex(0);
  
  // Inizializzo l'etichetta
  // Imposto la superficie
  lab->setSurface(&lcd);
  // Imposto la posizione
  lab->setLocation(createLocation(5,2));
  // Assegno l'icona
  lab->setIcon(icn);
  // Inizializzo il tutto e creo l'icona nella memoria dello schermo
  lab->begin();
  // Aggiungo il controllo lab alla finestra
  win->addControl(lab);
  // Disegno la finestra
  win->draw();
}

void loop() {
  // put your main code here, to run repeatedly:

}
