#include "GEvent.h"

GEvent::GEvent()
{
    //ctor
}


GEvent::~GEvent()
{
    //dtor
}


char* GEvent::getName(){
    return name;
}

void GEvent::setName(char n[]){
    strcpy(this->name, n);
}

void GEvent::setPosition(location l){
    position = l;
}

location GEvent::getPosition(){
    return position;
}

void GEvent::setSender(char sen[]){
    strcpy(sender, sen);
}

char* GEvent::getSender(){
    return sender;
}

void GEvent::throwEvent(){
    thrown = true;
}

bool GEvent::isThrown(){
    return thrown;
}

