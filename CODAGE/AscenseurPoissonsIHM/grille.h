#ifndef GRILLE_H
#define GRILLE_H

#include "interfacecan.h"

class Grille
{

    InterfaceCAN *pIcan;

public:

    Grille(InterfaceCAN *pIcan);

    void ouvrir();
    void fermer();

};

#endif // GRILLE_H
