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
    LPTHREAD_PARAMS pThreadContext[NB_MAX_THREADS];

    short  val;
    short  nbThread;

public:
    InterfaceCAN();

    void demarrerThread();
    void interrompreThread();
    void ouvrirCanal(short indexCanal);
    void fermerCanal();
    void getInfos();
    void initialiserControleur();
    void initialiserModeFonctionnement();
    void initialiserIdentificateur(t_CANframeType typeTrame, t_identTrame ident, USHORT dlc = 0);
    void initialiserMasque();
    void initialiserEvenementGlobal();
    void initialiserEvenement(t_identTrame ident);
    void demarrerControleur();
    void arreterControleur();
    void ecrireDonneeSommetAscenseur(UCHAR donnees);
    void ecrireDonneeCoffretPecheur(UCHAR donnees);
    void lireEtat(t_identTrame ident);
    void lireValeur();

    short listeCanaux();

    static void afficherEvenement(t_CANevent* pEvent, HANDLE hThread, short nbEvent);
    static DWORD WINAPI lireBuffer(LPVOID threadContext);

    string getCode(short val);
};

#endif // INTERFACECAN_H
