#ifndef POMPE_H
#define POMPE_H
#include "capteurs.h"

#include "interfacecan.h"

class Pompe
{

    InterfaceCAN *pIcan;
    Capteurs *pCapteurs;

public:

    Pompe(InterfaceCAN *pIcan);

    void demarrer(Capteurs *pCapteurs);
    bool detecterArret();
};

#endif // POMPE_H
