#ifndef CAGEASCENSEUR_H
#define CAGEASCENSEUR_H

#include "interfacecan.h"

class CageAscenseur
{

    InterfaceCAN *pIcan;

public:

    CageAscenseur(InterfaceCAN *pIcan);

    void monter();
    void descendre();

};

#endif // CAGEASCENSEUR_H
