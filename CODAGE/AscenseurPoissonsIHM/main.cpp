#include <QApplication>
#include "ihm.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    IHM ihm;
    ihm.show();
    
    return app.exec();
}
