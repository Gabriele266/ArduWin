#include <ArduCore.h>
#include <LiquidCrystal_I2C.h>

// Raccoglitore delle finestre
GWinList *windows = new GWinList("windows");
// Prima finestra
GWindow *first = new GWindow("first", "Primo");
GWindow *sec = new GWindow("second", "Secondo");

LiquidCrystal_I2C lcd(0x27, 20, 4);

int win_pos;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.clear();

  Serial.begin(57600);

  first->setSurface(&lcd);
  first->setBackBtnType(BackBtnType::Medium);
  first->setBackBtnPos(BackBtnPos::TopRight);
  first->setShowBackBtn(true);

  sec->setSurface(&lcd);
  sec->setBackBtnType(BackBtnType::Small);
  sec->setBackBtnPos(BackBtnPos::BottomCenter);
  sec->setShowBackBtn(true);
  win_pos = windows->add(first);
  
  windows->setMain(win_pos);
  windows->add(sec);
  
  // Mostra
  windows->drawMain();

  delay(3000);
  lcd.clear();
  windows->draw("second");
}

void loop() {
  // put your main code here, to run repeatedly:

}
