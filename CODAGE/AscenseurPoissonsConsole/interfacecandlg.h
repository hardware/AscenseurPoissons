#ifndef INTERFACECANDLG_H
#define INTERFACECANDLG_H

#include <iostream>

#include "interfacecan.h"
#include "ascpdef.h"

using namespace std;

class InterfaceCANDlg
{
    InterfaceCAN iCan;
    t_coffretPecheur coffretPecheur;
    t_sommetAscenseur sommetAscenseur;

public:

    InterfaceCANDlg();
    void run();

};

#endif // INTERFACECANDLG_H
