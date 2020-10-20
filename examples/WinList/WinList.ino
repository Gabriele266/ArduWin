#include <ArduWin.h>
#include <LiquidCrystal_I2C.h>

// Lista che conterrà le finestre
GWinList *list = new GWinList("Lista");

// Finestra principale
GWindow *main_win = new GWindow("main", "Main window");

// Seconda finestra
GWindow *sec = new GWindow("second", "Sec win");

// Rappresenta lo schermo
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(115200);
  // inizializzo lo schermo
  lcd.init();
  lcd.backlight();

  // imposto la superficie di disegno a tutte le finestre
  main_win->setSurface(&lcd);
  sec->setSurface(&lcd);

  // aggiungo le finestre alla lista
  list->addMain(main_win);
  Serial.println(list->getMainInd());
  list->add(sec);
}

void loop() {
  // disegno la finestra principale
  list->drawMain();
  // attendo
  delay(3000);
  list->draw("second");
  delay(3000);
  
}
