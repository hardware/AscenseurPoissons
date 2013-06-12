#include "interfacecan.h"

InterfaceCAN::InterfaceCAN()
{
    idCanal = INVALID_HANDLE_VALUE;
}

void InterfaceCAN::ouvrirCanal(short indexCanal)
{
    val = Ic_InitDrv(indexCanal, &idCanal);

    if(val != _OK)
        throw string("Ic_InitDrv : " + getCode(val));
}

void InterfaceCAN::fermerCanal()
{
    val = Ic_ExitDrv(idCanal);

    if(val != _OK)
        throw string("Ic_ExitDrv : " + getCode(val));
}

short InterfaceCAN::listeCanaux()
{
    string statut = "UTILISE";
    unsigned long nbCanaux;

    val = Ic_EnumCards(&nbCanaux, donneeCarte, sizeof( donneeCarte ));

    if(val != _OK)
        throw string("Liste des canaux non disponible");

    for(int i = 0; i < (int) nbCanaux; i++)
    {
        if(donneeCarte[i].cardAlreadyOpen == FALSE)
            statut = "LIBRE";

        cout << " - Canal : " << i << " | Statut -> " << statut << " | " << donneeCarte[i].cardNameString << endl;
    }

    if(nbCanaux < 1)
        throw string("Aucun canal disponible");

    return nbCanaux;
}

void InterfaceCAN::informationsPeripherique()
{

}

string InterfaceCAN::getCode(short val)
{
    switch(val)
    {
    case _OK : return "_OK";
    case _MEM_ERR : return "_MEM_ERR";
    case _SEQ_ERR : return "_SEQ_ERR";
    case _PARAM_ERR : return "_PARAM_ERR";
    case _CHIP_ERR : return "_CHIP_ERR";
    case _BOARD_ERR : return "_BOARD_ERR";
    case _ID_OVERFLOW : return "_ID_OVERFLOW";
    case _UNKNOWN_ID : return "_UNKNOWN_ID";
    case _UNKNOWN_PERIOD :  return "_UNKNOWN_PERIOD";
    case _PERIODIC_OVERFLOW :  return "_PERIODIC_OVERFLOW";
    case _EMPTY_BUF : return "_EMPTY_BUF";
    case _EMPTY_FIFO : return "_EMPTY_FIFO";
    case _FRAME_TYPE_ERR : return "_FRAME_TYPE_ERR";
    case _INTERFACE_ERR : return "_INTERFACE_ERR";
    case _BUF_OCCUPIED : return "_BUF_OCCUPIED";
    case _INVALID_OP : return "_INVALID_OP";
    case _DRV_PARAM_ERR : return "_DRV_PARAM_ERR";
    case _OPENING_DRV_ERR : return "_OPENING_DRV_ERR";
    case _SLEEP_MODE : return "_SLEEP_MODE";
    case _USB_ERR : return "_USB_ERR";
    case _RS232_ERR : return "_RS232_ERR";
    case _BOARD_TIMEOUT : return "_BOARD_TIMEOUT";
    default : return "_???";
    }
}

