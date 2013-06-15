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

public:

    InterfaceCANDlg();
    void run();

};

#endif // INTERFACECANDLG_H
