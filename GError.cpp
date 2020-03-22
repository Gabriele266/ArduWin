/*
* Autore:
* Versione:
* Descrizione:
* Progetto:
*
*/#include "GError.h"

GError::GError()
{
    //ctor
}

GError::GError(char send[], char name[]){
    strcpy(this->sender, send);
    strcpy(this->name, name);
}

void GError::setName(char n[]){
    strcpy(name, n);
}

char* GError::getName(){
    return name;
}

void GError::setSender(char send[]){
    strcpy(sender, send);
}

char* GError::getSender(){
    return sender;
}


void GError::setTimes(unsigned int val){
    times = val;
}

unsigned int GError::getTimes(){
    return times;
}

void GError::increaseTimes(){
    times += 1;
}

void GError::throw_error(){
    thrown = true;
}

void GError::setHeader(char head[]){
    strcpy(header, head);
}

char* GError::getHeader(){
    return header;
}

void GError::setLevel(ErrorLevel e){
    level = e;
}

ErrorLevel GError::getLevel(){
    return level;
}


