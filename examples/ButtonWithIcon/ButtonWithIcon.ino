/*
 * Esempio: ButtonWithIcon
 * Autore: Cavallo Gabriele
 * Tramite la libreria crea una finestra con un pulsante centrale e gli assegna un icona. Infine mostra tutto 
 * Licenza: GPL
 */
// Header di ArduWin
#include <ArduWin.h>
// Header per lo schermo
#include <LiquidCrystal_I2C.h>

// Rappresenta la finestra utilizzata
GWindow *newWin = new GWindow("win1", "Esempio 05");

// Rappresenta il pulsante nella finestra
GButton *newBtn = new GButton("btn1", "Puls");

// Rappresenta l'icona del pulsante
GIcon *btnIcon = new GIcon();

// Rappresenta lo schermo
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  // Inizializzo il seriale
  Serial.begin(115200);
  // Scrivo la versione della libreria
  Serial.println("Esempio 05 Arduino: ButtonWithIcon");
  Serial.print("Versione ArduWin: ");
  Serial.println(ARDUWIN_VERSION);
  // Inizializzo lo schermo
  lcd.init();
  lcd.backlight();

  // Inizializzo la finestra
  newWin->setSurface(&lcd);

  // Inizializzo l'icona per il pulsante
  // Imposto il codice per l'icona
  btnIcon->setCode(clock_icon);
  // Imposto l'indice della icona
  btnIcon->setIndex(0);

  // Inizializzo il pulsante
  // Imposto l'icona
  newBtn->setIcon(btnIcon);
  // Imposto la superficie
  newBtn->setSurface(&lcd);
  // Imposto la posizione
  newBtn->setLocation(createLocation(2,3));     // createLocation crea un oggetto location dati due interi x e y.
  // Preparo il pulsante
  newBtn->begin();
  
  // Aggiungo il pulsante alla finestra
  newWin->addControl(newBtn);
  // Disegno la finestra
  newWin->draw();
}

void loop() {
  // put your main code here, to run repeatedly:

}
