#ifndef POMPE_H
#define POMPE_H

#include "capteurs.h"
#include "interfacecan.h"

class Pompe
{

    InterfaceCAN *pIcan;
    Capteurs *pCapteurs;

public:

    Pompe(InterfaceCAN *pIcan, Capteurs *pCapteurs);

    void demarrer();
    bool detecterArret();
};

#endif // POMPE_H
