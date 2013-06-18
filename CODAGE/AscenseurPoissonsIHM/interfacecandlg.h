#ifndef INTERFACECANDLG_H
#define INTERFACECANDLG_H

#include "interfacecan.h"
#include "journalevenements.h"
#include "ascpihmdef.h"

#include <QDebug>

class InterfaceCANDlg
{

    InterfaceCAN *pIcan;
    JournalEvenements journal;

public:
    InterfaceCANDlg(InterfaceCAN *pIcan);
};

#endif // INTERFACECANDLG_H
