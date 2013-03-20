#ifndef CAGEASCENSEUR_H
#define CAGEASCENSEUR_H

#include "interfacecan.h"

class CageAscenseur
{

    InterfaceCAN *pIcan;

public:

    CageAscenseur(InterfaceCAN *pIcan);

};

#endif // CAGEASCENSEUR_H
