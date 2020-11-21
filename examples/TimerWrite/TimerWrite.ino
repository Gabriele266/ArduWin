/*
 * Esempio TimerWrite: viene creato un timer e impostato il tempo di aggiornamento
 * a 1 secondo. Ogni secondo questo timer scrive una frase sul seriale, tramite la chiamata
 * della funzione handleTimer, che viene impostata come gestore di tale evento.
 */
#include <ArduWin.h>

// Timer da utilizzare
GTimer timer(1000);

// Gestisce il tick del timer
void handleTimer(unsigned int elapsed_time, char *name){
    Serial.println("Passato un secondo");
}

void setup() {
    // Inizializzo il seriale
    Serial.begin(115200);
    // Imposto il nome del timer
    timer.setName("Timer");
    // Imposto il gestore della attivazione del timer
    timer.setActivationHandler(handleTimer);
    // Avvio il timer
    timer.start();
}

void loop() {
    // Aggiorno il timer
    timer.update();
    // Attendo 1 millisecondo
    delay(1);
}