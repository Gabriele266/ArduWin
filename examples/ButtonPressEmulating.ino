/*
 * Esempio 06: ButtonPressEmulating
 * In questo esempio creeremo una finestra con un pulsante e, su richiesta dell' utente tramite la comunicazione seriale 
 * emuleremo la pressione del pulsante.
 * Materiale necessario:
 *    Scheda Arduino
 *    Schermo lcd (va bene i2c o normale) --> in caso di lcd normale all' interno dei file GControl.h e GWindow.h cancellate la definizione del simbolo ARDUWIN_USE_I2C
 *    Cavetti
 */
// Header della libreria
#include <ArduWin.h>
// Header per lo schermo (utilizzo i2c) 
#include <LiquidCrystal_I2C.h>

// Rappresenta lo schermo (in caso di dimensioni minore cambiare i valori 20 e 4
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Rappresenta la finestra
GWindow *newWin = new GWindow("new", "Esempio 06");

// Rappresenta il pulsante
GButton *newBtn = new GButton("main", "premi");

// Funzione che gestisce la pressione del pulsante, quando avviene
// event contiene le informazioni sulla pressione del tasto, come l'oggetto padre, la posizione in cui è avvenuto etc...
void handler(GEvent *event){
  Serial.println("Premuto il pulsante main");
}

void setup() {
  // Inizializzo il seriale
  Serial.begin(57600);
  // Scrivo l'esempio
  Serial.println("Esempio 06 ButtonPressEmulating");
  Serial.println("Inviare il carattere c per emulare la pressione del pulsante");
  // Inizializzo lo schermo ( in caso di schermo lcd normale utilizzare lcd.begin() e la libreria LiquidCrystal
  lcd.init();
  lcd.backlight();
  // Inizializzo la finestra
  // Imposto il pulsante indietro
  newWin->setBackBtnPos(BackBtnPos::TopLeft);
  newWin->setBackBtnType(BackBtnType::Medium);
  newWin->setShowBackBtn(true);
  // Imposto la superficie
  newWin->setSurface(&lcd);
  // Inizializzo il pulsante
  // Imposto la superficie
  newBtn->setSurface(&lcd);
  newBtn->enable();
  // Imposto la posizione
  newBtn->setLocation(createLocation(4,2));
  // Imposto il gestore degli eventi
  newBtn->setEventHandler(handler);

  // Aggiungo il pulsante alla finestra
  newWin->addControl(newBtn);

  // Mostro la finestra
  newWin->draw();
}

void loop() {
  // Aspetto che l'utente abbia inviato il carattere c per emulare la pressione del pulsante
  if(Serial.available() > 0){
    char v = (char) Serial.read();
    if(v == 'c'){
      Serial.println("Ricevuto carattere c");
      // Emulo la pressione
      // Passo alla funzione per aggiornare lo stato dei controlli la posizione del pulsante
      newWin->updateControls(createLocation(6,2));
    }
  }
  
}
