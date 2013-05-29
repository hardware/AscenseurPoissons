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
    t_Interface *type // Mode de l'interface (BUFFER, FIFO... etc)
)
{

}

// Ic_InitId
bool InterfaceCAN::initialiserIdentificateur(
    HANDLE idCanal, // Identificateur du canal
    t_CANobj messageCAN // Structure des paramètres du message CAN
)
{

}

// Ic_ConfigEvent
bool InterfaceCAN::configurerEvenement(
    HANDLE idCanal, // Identificateur du canal
    HANDLE idEvenement, // Identificateur de l'évènement WIN32
    ulong identificateurCAN // Identificateur du message CAN
)
{

}

// Ic_InitDrv
bool InterfaceCAN::ouvrirCanal(
    HANDLE idCanal, // Identificateur du canal
    short indexCanal // Position (index) du canal à ouvrir
)
{

}

// Ic_ExitDrv
bool InterfaceCAN::fermerCanal(
    HANDLE idCanal // Identificateur du canal
)
{

}

// Ic_WriteData
bool InterfaceCAN::ecrireDonnee(HANDLE idCanal, // Identificateur du canal
    ulong idTrame, // Identificateur de la trame
    ushort tailleDonnee, // Taille des données à mettre à jour
    uchar *donnees ) // Pointeur sur un tableau d'octets contenant les données à mettre à jour
{

}

// Ic_GetBuf
bool InterfaceCAN::lireEtat(
    HANDLE idCanal, // Identificateur du canal
    ulong idTrame, // Identificateur de la trame
    t_CANevent *messageCAN // Structure des paramètres de l'évènement CAN
)
{

}

// Ic_GetBuf
float InterfaceCAN::lireValeur(
    HANDLE idCanal, // Identificateur du canal
    ulong idTrame, // Identificateur de la trame
    t_CANevent *messageCAN // Structure des paramètres de l'évènement CAN
)
{

}
