#ifndef CENTRALEHYDRAULIQUE_H
#define CENTRALEHYDRAULIQUE_H

#include "interfacecan.h"

class CentraleHydraulique
{

    InterfaceCAN *pIcan;

public:

    CentraleHydraulique(InterfaceCAN *pIcan);

    void demarrer();
    void arreter();

};

#endif // CENTRALEHYDRAULIQUE_H
