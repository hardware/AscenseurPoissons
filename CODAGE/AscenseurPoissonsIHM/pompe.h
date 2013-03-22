#ifndef POMPE_H
#define POMPE_H

#include "interfacecan.h"

class Pompe
{

    InterfaceCAN *pIcan;

public:

    Pompe(InterfaceCAN *pIcan);

    void demarrer();
    void arreter();

};

#endif // POMPE_H
