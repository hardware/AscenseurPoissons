#ifndef CENTRALEHYDRAULIQUE_H
#define CENTRALEHYDRAULIQUE_H

#include "interfacecan.h"
#include "capteurs.h"

class CentraleHydraulique
{

    InterfaceCAN *pIcan;
    Capteurs *pCapteurs;

public:

    CentraleHydraulique(InterfaceCAN *pIcan, Capteurs *pCapteurs);

    void demarrer();
    void arreter();

};

#endif // CENTRALEHYDRAULIQUE_H
