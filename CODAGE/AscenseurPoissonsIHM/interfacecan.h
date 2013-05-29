#ifndef INTERFACECAN_H
#define INTERFACECAN_H

#include <windows.h>
#include <conio.h>
#include <stdio.h>

#include "Canpcex.h"

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

    unsigned long idTrame;
    unsigned char donnees;

public:
    InterfaceCAN();
    float lireEtat(unsigned long IdTrame,unsigned short TailleDonnee,unsigned char Donnee);
    float lireValeur(unsigned long IdTrame,unsigned short TailleDonnee,unsigned char Donnee);
    short ecrireDonnees(unsigned long IdTrame,unsigned short TailleDonnee,unsigned char Donnee);
};

#endif // INTERFACECAN_H
