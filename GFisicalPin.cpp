//
// Created by Gabriele on 31/10/2020.
//
#ifndef FISICAL_PIN
#define FISICAL_PIN

#include "GFisicalPin.h"

GFisicalPin::GFisicalPin(char *n, nat number, PinType t, PinUseMode m, PinWaveMode wave){
    strcpy(name, n);
    pin = number;
    type = t;
    use_mode = m;
    mode = wave;
}

GFisicalPin::GFisicalPin(char *n, nat number) : GFisicalPin(n, number, PinType::Digital, PinUseMode::OutputMode, PinWaveMode::NormalWave){

}

GFisicalPin::GFisicalPin(char *n) : GFisicalPin(n, 0){

}

void GFisicalPin::setNumber(int number){
    pin = number;
}

int GFisicalPin::getNumber(){
    return pin;
}

PinType GFisicalPin::getType(){
    return type;
}

void GFisicalPin::setType(PinType t) {
    type = t;
}

bool GFisicalPin::exists(nat pin){
    // controllo se il pin esiste e non è un seriale
    if(pin <= 65 && pin != 0 && pin != 1){
        return true;
    }
    else{
        return false;
    }
}

void GFisicalPin::writeWave(PinWaveMode wave_mode, nat param){
    // Controllo se il pin è stato impostato correttamente
    if(exists(pin)){
        // controllo il tipo di onda da generare
        switch(wave_mode){
            case PinWaveMode::NormalWave:
                digitalWrite(pin, param);
                break;
            case PinWaveMode::PwmWave:
                analogWrite(pin, param);
                break;
            case PinWaveMode::SinusoidalWave:
                analogWrite(pin, param);
                break;
        }
        // salvo il tipo di onda generata
        mode = wave_mode;
        // Salvo il valore
        last_write_value = param;
    }
    else{
#ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GFisicalPin. Tentativo di generazione di una onda su un pin non esistente. ");
        launchParam("Pin", pin);
        launchParam("Nome", name);
        closeLaunch();
#endif
    }
}

void GFisicalPin::invertValue() {
    // controllare il tipo di onda applicata
    if(mode == PinWaveMode::NormalWave){
        // Controllo il valore del pin
        if(last_write_value >= 20){
            digitalWrite(pin, LOW);
            last_write_value = 0;
        }
        else{
            digitalWrite(pin, HIGH);
            last_write_value = 1024;
        }
    }
    else{
        // Controllo il valore del pin
        if(last_write_value >= 20){
            analogWrite(pin, LOW);
            last_write_value = 0;
        }
        else{
            analogWrite(pin, HIGH);
            last_write_value = 1024;
        }
    }
}

bool GFisicalPin::begin(){
    // controllo il pin
    if(exists(pin)){
        switch(use_mode){
            case PinUseMode::InputMode:
                pinMode(pin, INPUT);
                break;
            case PinUseMode::OutputMode:
                pinMode(pin, OUTPUT);
                break;
            case PinUseMode::NoMode:
#ifdef ENABLE_SERIAL_ERRORS
    launchError(" classe GFisicalPin. Tentativo di inizializzare un pin senza una modalità di accesso. ");
    launchParam("Pin", pin);
    launchParam("Nome", name);
    closeLaunch();
#endif
                break;
        }
    }
}

nat GFisicalPin::readValue(){
    // Controllo se il pin esiste
    if(exists(pin)){
        // Leggo il valore
        // Controllo il tipo di pin
        switch(type){
            case Pwm:
                return analogRead(pin);
            case Digital:
                return digitalRead(pin);
            case Analog:
                return analogRead(pin);
            case Builtin:
                return 5;
#ifdef ENABLE_SERIAL_ERRORS
                launchError(" classe GFisicalPin. Tentativo di lettura da un pin builtin");
                closeLaunch();
#endif
        }
    }
}

bool GFisicalPin::isHigh() {
    // Controllo che il pin esista e non sia builtin
    if(exists(pin) && pin != 13){
        if(digitalRead(pin) == 0){
            return false;
        }
        else{
            return true;
        }
    }
    else{
#ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GFisicalPin. Tentativo di lettura digitale da un pin non esistente. ");
        launchParam("Pin", pin);
        closeLaunch();
#endif
    }
}

#endif
