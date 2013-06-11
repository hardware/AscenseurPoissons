#ifndef INTERFACECANDLG_H
#define INTERFACECANDLG_H

#include <iostream>

#include "interfacecan.h"

using namespace std;

class InterfaceCANDlg
{
    InterfaceCAN iCan;

public:

    InterfaceCANDlg();
    void run();

};

#endif // INTERFACECANDLG_H
