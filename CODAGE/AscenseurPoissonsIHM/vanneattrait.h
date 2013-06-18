#ifndef VANNEATTRAIT_H
#define VANNEATTRAIT_H

#include "interfacecan.h"
#include "capteurs.h"

class VanneAttrait
{

    InterfaceCAN *pIcan;
    Capteurs *pCapteurs;

public:

    VanneAttrait(InterfaceCAN *pIcan, Capteurs *pCapteurs);

    void ouvrir();
    void fermer();

};

#endif // VANNEATTRAIT_H
