#ifndef GRILLE_H
#define GRILLE_H

#include "interfacecan.h"

class Grille
{

    InterfaceCAN *pIcan;

public:

    Grille(InterfaceCAN *pIcan);

};

#endif // GRILLE_H
