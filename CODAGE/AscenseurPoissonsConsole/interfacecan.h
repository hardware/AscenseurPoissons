#ifndef INTERFACECAN_H
#define INTERFACECAN_H

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <QVariant>
#include <QDebug>

#include "Canpcex.h"
#include "ascpdef.h"

using namespace std;

class InterfaceCAN
{
    HANDLE idCanal;
    ULONG  idTrame;
    UCHAR  donnees;
    short  val;
    short  nbThread;

    t_CANobj        messageCAN;
    t_CANbusParams  parametresBUS;
    t_CANdeviceInfo infosCarte;
    t_CardData      donneeCarte[10];

    LPTHREAD_PARAMS pThreadContext[NB_MAX_THREADS];

public:
    InterfaceCAN();

    string getCode(short val);
    short listeCanaux();
    void demarrerThread();
    void interrompreThread();
    void ouvrirCanal(short indexCanal);
    void fermerCanal();
    void getInfos();
    void initialiserControleur();
    void initialiserModeFonctionnement();
    void initialiserIdentificateur(t_CANframeType typeTrame, ushort dlc = 0);
    void initialiserMasque();
    void initialiserEvenementGlobal();
    void initialiserEvenement();
    void demarrerControleur();
    void arreterControleur();
    void ecrireDonnee();
    void setIdTrame(ULONG idTrame);
    void setDonnees(UCHAR donnees);

    static void afficherEvenement(t_CANevent* pEvent, HANDLE hThread, short nbEvent);
    static DWORD WINAPI lireBuffer(LPVOID threadContext);
};

#endif // INTERFACECAN_H
