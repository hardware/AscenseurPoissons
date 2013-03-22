#ifndef VANNEATTRAIT_H
#define VANNEATTRAIT_H

#include "interfacecan.h"

class VanneAttrait
{

    InterfaceCAN *pIcan;

public:

    VanneAttrait(InterfaceCAN *pIcan);

    void ouvrir();
    void fermer();

};

#endif // VANNEATTRAIT_H
