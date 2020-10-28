//
// Created by Gabriele on 28/10/2020.
//

#ifndef ARDUWIN_GSEPARATOR_H
#define ARDUWIN_GSEPARATOR_H

#include "GControl.h"

/// Rappresenta un separatore in arduwin
class GSeparator : GControl{
public:
    GSeparator();
    GSeparator(char t);

    /// Disegna il controllo
    bool draw();
private:
};


#endif //ARDUWIN_GSEPARATOR_H
