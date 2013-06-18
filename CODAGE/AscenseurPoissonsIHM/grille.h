#ifndef GRILLE_H
#define GRILLE_H

#include "interfacecan.h"
#include "capteurs.h"

class Grille
{

    InterfaceCAN *pIcan;
    Capteurs *pCapteurs;

public:

    Grille(InterfaceCAN *pIcan, Capteurs *pCapteurs);

    void ouvrir();
    void fermer();

};

#endif // GRILLE_H
