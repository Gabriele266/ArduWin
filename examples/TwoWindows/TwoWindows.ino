/*
 * Autore: Cavallo Gabriele
 * Esempio Two_Windows, tramite la libreria ArduWin crea un raccoglitore di 
 * finestre GWinList e gli inserisce due nuove finestre: una chiamata first e una second.
 * Infine gestisce la loro visualizzazione: imposta first come finestra principale e la mostra; dopo 3 secondi mostra la finestra second tramite la funzione di ricerca tramite il nome.
 * ATTENZIONE: Per evitare problemi di utilizzo della ram si consiglia l'utilizzo della libreria con schede Arduino Mega o Due.
 */

// Header di ArduWin
#include <ArduWin.h>
// Liberia per lo schermo
#include <LiquidCrystal_I2C.h>

// Raccoglitore delle finestre
// Contiene tutte le finestre dell' esempio
// Viene inizializzato con un nome: windows
GWinList *windows = new GWinList("windows");
// Prima finestra dell' esempio
// Inizializzo la finestra nello heap della ram e gli assegno il nome e il titolo
GWindow *first = new GWindow("first", "Primo");
// Seconda finestra
// Viene mostrata dopo 3 secondi dall' inizio
GWindow *sec = new GWindow("second", "Secondo");
// Schermo lcd sull indirizzo 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);
// Indice della finestra principale nel raccoglitore windows
// Viene restituita all' aggiunta della finestra nella lista
int win_pos;

void setup() {
  // inizializzo lo schermo lcd
  lcd.init();
  // Attivo la retroilluminazione
  lcd.backlight();
  // Pulisco lo schermo
  lcd.clear();
  // Inizializzo il seriale
  Serial.begin(57600);

  // Formatto la prima finestra, quella principale
  // Assegno la superficie da utilizzare per disegnarla
  // ATTENZIONE: La funzione per impostarla accetta un puntatore
  first->setSurface(&lcd);
  // Formatto il pulsante indietro predefinito
  // Assegno la tipologia
  // Tipi possibili: Small Medium Large
  first->setBackBtnType(BackBtnType::Medium);
  // Assegno la posizione assoluta nello schermo
  first->setBackBtnPos(BackBtnPos::TopRight);
  // Avvio la visualizzazione del pulsante indietro
  first->setShowBackBtn(true);

  // Formatto la seconda finestra
  // Imposto la superficie
  sec->setSurface(&lcd);
  // Imposto il pulsante indietro
  sec->setBackBtnType(BackBtnType::Small);
  sec->setBackBtnPos(BackBtnPos::BottomCenter);
  sec->setShowBackBtn(true);

  // Aggiungo la finestra first al raccoglitore windows e salvo l'indice in cui è stata messa (ora è 0 perchè è la prima)
  win_pos = windows->add(first);

  // Contrassegno la finestra come principale
  windows->setMain(win_pos);    // Utilizzo l'indice che mi ero salvato
  // Aggiungo la seconda finestra
  windows->add(sec);
  
  // Mostro la finestra principale (first)
  windows->drawMain();

  // Attendo 3 secondi
  delay(3000);
  // Pulisco lo schermo
  lcd.clear();
  // Mostro la seconda
  windows->draw("second");
}

void loop() {
  // put your main code here, to run repeatedly:

}
