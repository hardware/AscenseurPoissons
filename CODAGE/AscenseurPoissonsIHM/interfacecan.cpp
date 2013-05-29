#include "interfacecan.h"

InterfaceCAN::InterfaceCAN()
{
}

// Ic_StartChip
bool InterfaceCAN::demarrerControleur(
    HANDLE idCanal // Identificateur du canal
)
{

}

// Ic_InitChip
bool InterfaceCAN::initialiserControleur(
    HANDLE idCanal, // Identificateur du canal
    t_CANbusParams *parametresBUS, // Paramètres du BUS (débit, échantillonnage...etc)
    t_CANaddressing *adressageCAN, // Type d'adressage
    t_CANpadding *padding // Taille des trames CAN
)
{

}

// Ic_InitInterface
bool InterfaceCAN::initialiserModeFonctionnement(
    HANDLE idCanal, // Identificateur du canal
    t_Interface *type )
{

}

// Ic_InitId
bool InterfaceCAN::initialiserIdentificateur(
    HANDLE idCanal, // Identificateur du canal
    t_CANobj messageCAN )
{

}

// Ic_ConfigEvent
bool InterfaceCAN::configurerEvenement(
    HANDLE idCanal, // Identificateur du canal
    HANDLE idEvenement,
    ulong identificateurCAN )
{

}

// Ic_InitDrv
bool InterfaceCAN::ouvrirCanal(
    HANDLE idCanal, // Identificateur du canal
    short indexCanal )
{

}

// Ic_ExitDrv
bool InterfaceCAN::fermerCanal(
    HANDLE idCanal // Identificateur du canal
)
{

}

// Ic_WriteData
bool InterfaceCAN::ecrireDonnee(
    HANDLE idCanal, // Identificateur du canal
    ulong idTrame,
    ushort tailleDonnee,
    uchar donnees )
{

}

// Ic_GetBuf
bool InterfaceCAN::lireEtat(
    HANDLE idCanal, // Identificateur du canal
    ulong idTrame,
    t_CANevent *messageCAN )
{

}

// Ic_GetBuf
float InterfaceCAN::lireValeur(
    HANDLE idCanal, // Identificateur du canal
    ulong idTrame,
    t_CANevent *messageCAN )
{

}
