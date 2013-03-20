#ifndef CAPTEURS_H
#define CAPTEURS_H

#include "interfacecan.h"

class Capteurs
{

    InterfaceCAN *pIcan;

public:

    Capteurs(InterfaceCAN *pIcan);

};

#endif // CAPTEURS_H
