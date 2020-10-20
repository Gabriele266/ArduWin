#include "GCheckBox.h"

GCheckBox::GCheckBox(char name[], char cont[], location l){
    // Costruttore base
    // Impostoi il nome e il contenuto
    setName(name);
    setText(cont);
    setLocation(l);

    // Creo le due icone
    checkedIcon = new GIcon();
    checkedIcon->setCode(checked_icon);
    // Imposto l'indice 4
    checkedIcon->setIndex(4);

    // Creo l'icona unchecked
    uncheckedIcon = new GIcon();
    uncheckedIcon->setCode(unchecked_icon);
    uncheckedIcon->setIndex(5);
    // Azzero checked
    checked = false;
}

GCheckBox::GCheckBox() : GCheckBox("", "", createLocation())
{
    //ctor
}

GCheckBox::GCheckBox(char name[], char cont[]) : GCheckBox(name, cont, createLocation()){
    // Niente
}


void GCheckBox::check(){
    checked = true;
}

void GCheckBox::unCheck(){
    checked = false;
}

bool GCheckBox::isChecked(){
    return checked;
}

void GCheckBox::setChecked(bool val){
    checked = val;
}

bool GCheckBox::begin(){
    // conrollo se è stata specificata una superficie di disegno
    if(getSurface() != nullptr){
        // controllo se snono state impostate le icone
        if(checkedIcon != nullptr && uncheckedIcon != nullptr){
            // Inizializzo la icona checked
            getSurface()->createChar(checkedIcon->getIndex(), checkedIcon->getCode());
            // Inizializzo la iocona unchecked
            getSurface()->createChar(uncheckedIcon->getIndex(), uncheckedIcon->getCode());
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool GCheckBox::draw(){
    // Controllo la surface
    if(getSurface() != nullptr){
        // Posiziono l'icona
        // Metto l'icona checked
        getSurface()->setCursor(getLocation().x, getLocation().y);
        if(checked){
            // Metto l'icona checked
            getSurface()->write(byte(checkedIcon->getIndex()));
        }
        else{
            // Metto l'icona unchecked
            getSurface()->write(byte(uncheckedIcon->getIndex()));
        }
        // Metto il testo
        getSurface()->print(getText());
        return true;
    }
    else{
        return false;
    }
}


void GCheckBox::updateEvents(location l){
    // controllo che esista la superficie
    if(getSurface() != nullptr){
        // Controllo che eistano tutti e che la posizione appartenga al pulsante
        if(exists(l) && exists(getLocation()) && isInArea(l,getLocation(), strlen(getText()))){
             //Sono stato premuto
             // Inverto lo stato e ridisegno
             getSurface()->setCursor(getLocation().x, getLocation().y);
             checked = !checked;
             if(checked){
                getSurface()->write(byte(checkedIcon->getIndex()));
             }
             else{
                // Metto l'icona unchecked
                getSurface()->write(byte(uncheckedIcon->getIndex()));
             }
        }
    }
    else{

    }
}
