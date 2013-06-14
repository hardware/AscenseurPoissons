﻿#ifndef INTERFACECAN_H
#define INTERFACECAN_H

#include <windows.h>
#include <iostream>
#include <string>

#include "Canpcex.h"
#include "types.h"

using namespace std;

class InterfaceCAN
{

    HANDLE hMutex;
    HANDLE idCanal;
    LPDWORD threadId;

    t_CANobj messageCAN;
    t_CANbusParams parametresBUS;
    t_CANdeviceInfo infosCarte;
    t_CardData donneeCarte[10];

    ulong idTrame;
    uchar donnees;
    short val;

    t_ThreadContext contextThread[2];

public:
    InterfaceCAN();

    string getCode(short val);

    short listeCanaux();
    void ouvrirCanal(short indexCanal);
    void fermerCanal();
    void getInfos();
    void initialiserControleur();
    void initialiserModeFonctionnement();
    void initialiserIdentificateur(t_CANframeType typeTrame, short tailleDonnee = 8);
    void demarrerControleur();
    void arreterControleur();
    void ecrireDonnee();
    void creerThread();
    DWORD thread();

    void setIdTrame(ulong idTrame);
    void setDonnees(uchar donnees);

    /*
    bool configurerEvenement(HANDLE idCanal, HANDLE idEvenement, ulong identificateurCAN);
    bool lireEtat(HANDLE idCanal, ulong idTrame, t_CANevent *messageCAN);
    float lireValeur(HANDLE idCanal, ulong idTrame, t_CANevent *messageCAN);
    */
};

#endif // INTERFACECAN_H
