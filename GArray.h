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

    /// Ridimensiona l'array
    bool resize(nat new_dim);

    /// Ridimensiona l'array e rimuove gli elementi che rimarrebbero unhowned
    bool resize(nat new_dim, bool remove_others);

    /// Restituisce le dimensioni dell' array
    nat getSize(){
        return count;
    }

    /// Restituisce le dimensioni massime dell' array
    nat getMaxSize() {
        return dim;
    }

    /// Pulisce l'array cancellando tutti gli elementi
    void clear();

    /// Esegue la funzione function su tutti gli elementi esistenti
    void execute(void (*function)(t *current, nat current_ind));

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
    closeLaunch();
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
    closeLaunch();
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
        closeLaunch();
        #endif
        return nullptr;
    }
}

template <class t, nat dim>
void GArray<t, dim>::execute(void (*function)(t *current, nat current_ind)){
    // Scorro gli elementi attivi dell' array
    for(int cur = 0; cur < count; cur ++){
        // Controllo che l'elemento corrente non sia nullptr
        if(elems[cur] != nullptr){
            // eseguo la funzione
            function(elems[cur], cur);
        }
        else{
            #ifdef ENABLE_SERIAL_ERRORS
            launchError(" classe GArray. Esecuzione funzione non riuscita su elemento nullo in array. ");
            launchParam("Indice", cur);
            launchParam("Numero elementi", count);
            closeLaunch();
            #endif
        }
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
            closeLaunch();
            #endif
        }
    }
    else{
        return false;
    }
}

template <class t, nat dim>
bool GArray<t, dim>::resize(nat new_dim){
    // controllo che la nuova dimensione sia contenuta in quella massima
    if(new_dim < dim){
        count = new_dim;
    }
    else{
        #ifdef ENABLE_SERIAL_ERRORS
        launchError(" classe GArray. Tentativo di ridimensionamento con valore troppo grande.");
        launchParam("Nuova dimensione", new_dim);
        // launchParam("Dimensione massima", dim);
        launchParam("Dimensione corrente", count);
        launchParam("Funzione", "resize(unsigned int new_dim)");
        closeLaunch();
        #endif
    }
}

template <class t, nat dim>
bool GArray<t, dim>::resize(nat new_dim, bool remove_others){
    // controllo se posso cambiare le dimensioni
    if(resize(new_dim)){
        // cancello gli elementi
        if(new_dim < count - 1){
            // rimuovo gli elementi rimasti fuori
            for(int x = new_dim; x < count; x++){
                elems[x] = nullptr;
            }
        }
        return true;
    }
    return false;
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
        closeLaunch();
        #endif
        return nullptr;
    }
}

template <class t, nat dim>
void GArray<t, dim>::clear(){
    // scorro gli elementi
    for(int x = 0; x < dim; x ++){
        elems[x] = nullptr;
    }
}
#endif