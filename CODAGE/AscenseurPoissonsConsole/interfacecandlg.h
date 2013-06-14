#ifndef INTERFACECANDLG_H
#define INTERFACECANDLG_H

#include <iostream>
#include <QVariant>

#include "interfacecan.h"
#include "typesInterfaceLogicielle.h"

using namespace std;

class InterfaceCANDlg
{
    InterfaceCAN iCan;
    coffretPecheur coffret;

public:

    InterfaceCANDlg();
    void run();

};

#endif // INTERFACECANDLG_H
