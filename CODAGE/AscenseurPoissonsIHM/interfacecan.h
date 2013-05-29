#ifndef INTERFACECAN_H
#define INTERFACECAN_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "Canpcex.h"
#include "types.h"

class InterfaceCAN
{

    HANDLE hMutex;
    HANDLE idCanal;
    HANDLE idEvenement;
    DWORD threadId;

    t_CANobj messageCAN;
    t_CANbusParams parametresBUS;
    t_CardData donneeCarte;
    t_Interface typeInterface;

    ulong idTrame;
    uchar donnees;

public:
    InterfaceCAN();

    bool demarrerControleur(HANDLE idCanal);
    bool initialiserControleur(HANDLE idCanal, t_CANbusParams *parametresBUS, t_CANaddressing *adressageCAN, t_CANpadding *padding);
    bool initialiserModeFonctionnement(HANDLE idCanal, t_Interface *type);
    bool initialiserIdentificateur(HANDLE idCanal, t_CANobj messageCAN);
    bool configurerEvenement(HANDLE idCanal, HANDLE idEvenement, ulong identificateurCAN);
    bool ouvrirCanal(HANDLE idCanal, short indexCanal);
    bool fermerCanal(HANDLE idCanal);
    bool ecrireDonnee(HANDLE idCanal, ulong idTrame, ushort tailleDonnee, uchar donnees);
    bool lireEtat(HANDLE idCanal, ulong idTrame, t_CANevent *messageCAN);
    float lireValeur(HANDLE idCanal, ulong idTrame, t_CANevent *messageCAN);
};

#endif // INTERFACECAN_H
