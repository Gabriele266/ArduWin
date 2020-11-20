/*
 * Autore: Cavallo Gabriele
 * Esempio redrawcontrol, composto da una finestra con una etichetta, il suo testo viene cambiato periodicamente
 * e si può osservare come viene ridisegnato
 */
#include <ArduWin.h>
#include <LiquidCrystal_I2C.h>

// Finestra
GWindow *win = new GWindow("nome", "titolo");

// Etichetta
GLabel *label = new GLabel("nome", "Testo");

// Rappresenta lo schermo
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Indica se il ciclo è al primo o secondo giro
bool first_cicle = true;

void setup() {
    // Avvio il seriale
    Serial.begin(115200);
    Serial.println("Esempio RedrawControl");

    // Inizializzo lo schermo
    lcd.init();
    lcd.backlight();
    // Pulisco lo schermo
    lcd.clear();

    // Imposto la superficie di disegno per la finestra
    win->setSurface(&lcd);
    // Imposto la superficie di disegno per l'etichetta
    label->setSurface(&lcd);

    // imposto la posizione della etichetta
    label->setLocation(createLocation(3, 2));

    // Aggiungo l'etichetta alla finestra
    win->add(label);

    // mostro la finestra
    win->draw();
}

void loop() {
    if(first_cicle){
        label->setText("Secondo c");
        first_cicle = false;
    }
    else{
        label->setText("Primo c");
        first_cicle = true;
    }
    delay(1000);
}