#include <QCoreApplication>
#include "interfacecandlg.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    InterfaceCANDlg dlg;
    dlg.run();
    
    return a.exec();
}
