/*
 * Autore: Cavallo Gabriele
 * Descrizione: File di esempio per la creazione di una finestra con schermo lcd i2c
 * 
 * Il programma crea un oggetto liquidrcystal i2c, una finestra e la mostra
 */
#include <ArduWin.h>
#include <LiquidCrystal_I2C.h>

// Creo la finestra
GWindow *win = new GWindow("Nome", "Ciao");

GCheckBox *ck = new GCheckBox("Nome", "Cont", createLocation(2,2));

// Creo l'oggetto I2c
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Inizializzo lo schermo
  lcd.init();
  lcd.backlight();
  ck->setSurface(&lcd);
  ck->begin();
  // Imposto la superficie per il disegno
  win->setSurface(&lcd);
  
  win->addControl(ck);
  
  // Disegno la finestra
  win->draw();

  
}

void loop() {
  // put your main code here, to run repeatedly:
  // simulo la pressione di un tasto sul controllo
  win->updateControls(createLocation(2,2));
  delay(3000);
}
