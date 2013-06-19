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

/**
 * @class InterfaceCAN
 * @brief Classe representant l'interface CAN
 *
 * Cette classe permet de configurer et d'utiliser la carte CAN de chez NSI
 */
class InterfaceCAN
{
    /**
     * HANDLE du canal choisi
     */
    HANDLE idCanal;

    /**
     * Pointeur sur un tableau de structures contenant les paramètres des threads
     */
    LPTHREAD_PARAMS pThreadContext[NB_MAX_THREADS+1];

    /**
     * Valeur de retour des primitives de la librairie
     */
    short  val;

    /**
     * Index du contexte correspondant au thread
     */
    short  indexThread;

public:
    InterfaceCAN();
    ~InterfaceCAN();

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
    void ecrireDonneeSommetAscenseur(unsigned char *dataArray);
    void ecrireDonneeCoffretPecheur(unsigned char *dataArray);
    void lireEtat(t_identTrame ident);
    void lireValeur();

    short listeCanaux();

    static void afficherEvenement(t_CANevent* pEvent, HANDLE hThread, short nbEvent);
    static DWORD WINAPI lireBuffer(LPVOID threadContext);

    string getCode(short val);
};

#endif // INTERFACECAN_H
