#ifndef CAGEASCENSEUR_H
#define CAGEASCENSEUR_H

#include "interfacecan.h"
#include "capteurs.h"

class CageAscenseur
{

    InterfaceCAN *pIcan;
    Capteurs *pCapteurs;

public:

    CageAscenseur(InterfaceCAN *pIcan, Capteurs *pCapteurs);

    void monter();
    void descendre();

};

#endif // CAGEASCENSEUR_H
