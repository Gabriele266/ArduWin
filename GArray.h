/*
    Autore: cavallo gabriele

*/
#ifndef GARRAY_CPP
#define GARRAY_CPP  

// Header di arduino
#include <Arduino.h>
// Header con modalità di esecuzione
#include "flags.cpp"

/// Rappresenta un numero naturale
typedef unsigned int nat;

/// Rappresenta un array di elementi
template <class t, nat dim>
class GArray{
public:
    // Costruttore
    GArray();
    
    // Funzione per aggiungere un elemento
    void add(t *elem);

    /// Imposta l'elemento index
    bool set(nat index, t *elem);

    /// Determina se esiste un elemento in quella posizione
    bool exists(nat index);

    /// Determina se esiste un elemento in quella posizione e controlla che non sia nullo
    bool exists(nat index, bool check_nullptr);

    /// Restituisce l'elemento relativo a quell ' indice se esiste
    t* get(nat index);

    /// Operatore di accesso
    t* operator[](nat index);
private:
    // Array con gli elementi
    t *elems[dim];
    // Numero di elementi
    nat count = 0;
};

template <class t, nat dim>
GArray<t, dim>::GArray(){
    count = 0;
}

template <class t, nat dim>
void GArray<t, dim>::add(t *elem){
    elems[count] = elem;
    count ++;
}


template <class t, nat dim>
bool GArray<t, dim>::exists(nat index){
    // controllo se esiste
    if(index >= 0 && index < count && elems[index] != nullptr){
        return true;
    }
    #ifdef ENABLE_SERIAL_WARNINGS
    launchWarning(" classe GArray ricerca elemento in array ha restiuito false. ");
    launchParam("Indice ricerca", index);
    launchParam("Funzione", "exists(unsigned int index)");
    #endif
    return false;
}

template <class t, nat dim>
bool GArray<t, dim>::exists(nat index, bool check_nullptr){
    // controllo se esiste
    if(index >= 0 && index < count){
        // controllo il nullptr
        if(check_nullptr){
            // controllo il puntatore
            if(elems[index] != nullptr){
                return true;
            }
            else{
                return false;
            }
        }
        return true;   
    }
    #ifdef ENABLE_SERIAL_WARNINGS
    launchWarning(" classe GArray ricerca elemento in array ha restiuito false. ");
    launchParam("Indice ricerca", index);
    launchParam("Funzione", "exists(unsigned int index, bool check_nullptr)");
    launchParam("Ricerca nullptr", check_nullptr);
    #endif
    return false;
}

template <class t, nat dim>
t* GArray<t, dim>::operator[](nat ind){
    // controllo se esiste un elemento
    if(exists(ind)){
        return elems[ind];
    }
    else{
        #ifdef ENABLE_SERIAL_WARNINGS
        launchWarning(" classe GArray ricerca elemento in array non esistente. E' stato restituito nullptr");
        launchParam("Indice", ind);
        launchParam("Funzione", "operator[](unsigned int ind)");
        #endif
        return nullptr;
    }
}

template <class t, nat dim>
bool GArray<t, dim>::set(nat index, t *val){
    // controllo se esiste un elemento nell' array
    if(exists(index, false)){
        // L'elemento esiste
        // controllo che il nuovo elemento non sia nullptr
        if(val != nullptr){
            // lo sovrascrivo
            elems[index] = val;
            return true;
        }
        else{
            #ifdef ENABLE_SERIAL_ERRORS
            launchError(" tentativo di impostazione di un valore esterno all' array");
            launchParam("Indice", index);
            #endif
        }
    }
    else{
        return false;
    }
    
}

template <class t, nat dim>
t* GArray<t, dim>::get(nat ind){
    // controllo se esiste l'elemento
    if(exists(ind, false)){
        return elems[ind];
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GArray tentativo di accesso a un elemento non esistente. ");
        launchParam("Indice", ind);
        #endif
        return nullptr;
    }
}
#endif