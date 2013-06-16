﻿#include "interfacecan.h"

InterfaceCAN::InterfaceCAN()
{
    idCanal = INVALID_HANDLE_VALUE;

    for(int i = 0; i < 2; i++)
        pThreadContext[i] = (LPTHREAD_PARAMS)malloc(sizeof(THREAD_PARAMS));
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
    short nbCanaux;

    val = Ic_EnumCards( (ulong*)&nbCanaux, donneeCarte, sizeof(donneeCarte));

    if(val != _OK)
        throw string("Liste des canaux non disponible");

    for(int i = 0; i < (int)nbCanaux; i++)
    {
        if(donneeCarte[i].cardAlreadyOpen == FALSE)
            statut = "LIBRE";

        cout << " - Canal : " << i << " | Statut -> " << statut << " | " << donneeCarte[i].cardNameString << endl;
    }

    if(nbCanaux < 1)
        throw string("Aucun canal disponible");

    return nbCanaux;
}

void InterfaceCAN::getInfos()
{
    short DLL, DRV;

    val = Ic_GetDeviceInfo(idCanal, &infosCarte);

    if(val != _OK)
        throw string("Ic_GetDeviceInfo : " + getCode(val));

    cout << "- Nom : " << infosCarte.CAN_USB.productName << endl;
    cout << "- Fabricant : " << infosCarte.CAN_USB.manufacturerName << endl;
    cout << "- Numero de serie : " << infosCarte.CAN_USB.serialNumber << endl;

    printf("- Version du firmware : %.2f \n", infosCarte.CAN_USB.firmwareVersion/100.0);
    printf("- Version du materiel : %.2f \n", infosCarte.CAN_USB.hardwareVersion/100.0);

    val = Ic_GetAPIinfo(idCanal, &DLL, &DRV, NULL);

    if(val != _OK)
        throw string("Ic_GetAPIinfo : " + getCode(val));

    printf("- Version du driver : %.2f \n", DRV/100.0);
    printf("- Version de la DLL : %.2f \n", DLL/100.0);
}

void InterfaceCAN::initialiserControleur()
{
    // Réglage pour un débit de 250 kBits/s et un point d'échantillonnage à 75% et 1 échantillon
    parametresBUS.baudpresc = 2; // BRP
    parametresBUS.tseg1 = 11; // Segment précédent le point d'échantillonnage
    parametresBUS.tseg2 = 4; // Segment suivant le point d'échantillonnage
    parametresBUS.sjw = 1; // Synchronisation Jump Width
    parametresBUS.sample = 0; // 0 pour 1 échantillon et 1 pour 3 échantillon

    printf("- BRP : %d \n", parametresBUS.baudpresc);
    printf("- TSEG1 : %d \n", parametresBUS.tseg1);
    printf("- TSEG2 : %d \n", parametresBUS.tseg2);
    printf("- SJW : %d \n", parametresBUS.sjw);
    printf("- SAMPLE : %d \n", parametresBUS.sample);

    cout << endl;
    cout << "Debit : 250 kBits/s\nPoint d'echantillonnage : 75%\nNombre d'echantillons : 1" << endl;

    val = Ic_InitChip(idCanal, parametresBUS, _DC_EXTENDED, _DC_NO_PADDING);

    if(val != _OK)
        throw string("Ic_InitChip : " + getCode(val));
}

void InterfaceCAN::initialiserModeFonctionnement()
{
    val = Ic_InitInterface(idCanal, _BUFFER);

    if(val != _OK)
        throw string("Ic_InitInterface : " + getCode(val));
}

void InterfaceCAN::initialiserIdentificateur(t_CANframeType typeTrame, ushort dlc)
{
    messageCAN.ident = idTrame;
    messageCAN.identType = _CAN_STD;
    messageCAN.frameType = typeTrame;
    messageCAN.dlc = dlc;

    val = Ic_InitId(idCanal, &messageCAN);

    if(val != _OK)
        throw string("Ic_InitId : " + getCode(val));
}

void InterfaceCAN::initialiserMasque()
{
    val = Ic_SetRxMask(idCanal, 0x000, 0x001, _CAN_STD);

    if(val != _OK)
        throw string("Ic_SetRxMask : " + getCode(val));
}

void InterfaceCAN::initialiserEvenement()
{
    pThreadContext[0]->ident  = idTrame;
    pThreadContext[0]->hCanal = idCanal;
    pThreadContext[0]->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    pThreadContext[1]->ident  = _CAN_DUMMY_ID;
    pThreadContext[1]->hCanal = idCanal;
    pThreadContext[1]->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    if(pThreadContext[0]->hEvent == NULL || pThreadContext[1]->hEvent == NULL)
        throw string("Une erreur est survenue lors de la creation des evenements");

    val = Ic_ConfigEvent(idCanal, pThreadContext[0]->hEvent, idTrame);

    if(val != _OK)
        throw string("Ic_ConfigEvent Thread[0] : " + getCode(val));

    val = Ic_ConfigEvent(idCanal, pThreadContext[1]->hEvent, _CAN_DUMMY_ID);

    if(val != _OK)
        throw string("Ic_ConfigEvent Thread[1] : " + getCode(val));
}

void InterfaceCAN::demarrerControleur()
{
    val = Ic_StartChip(idCanal);

    if(val != _OK)
        throw string("Ic_StartChip : " + getCode(val));
}

void InterfaceCAN::arreterControleur()
{
    val = Ic_StopChip(idCanal);

    if(val != _OK)
        throw string("Ic_StopChip : " + getCode(val));
}

void InterfaceCAN::ecrireDonnee()
{    
    val = Ic_TxMsg(idCanal, idTrame, sizeof(donnees), &donnees);

    if(val != _OK)
        throw string("Ic_TxMsg : " + getCode(val));
}

void InterfaceCAN::demarrerThread()
{
    for(int i = 0; i < 2; i++)
    {
        pThreadContext[i]->hThread = CreateThread(
            NULL,
            0,
            (LPTHREAD_START_ROUTINE)lireBuffer,
            (LPVOID)pThreadContext[i],
            0,
            NULL
        );

        if(pThreadContext[i]->hThread == NULL)
            throw string("Une erreur est survenue lors de la creation d un thread");
    }
}

void InterfaceCAN::interrompreThread()
{
    for(int i = 0; i < 2; i++)
    {
        if(pThreadContext[i]->hThread)
            TerminateThread(pThreadContext[i]->hThread, 0);

        if(pThreadContext[0]->hEvent)
            CloseHandle(pThreadContext[0]->hEvent);
    }
}

void InterfaceCAN::setIdTrame(ULONG idTrame)
{
    this->idTrame = idTrame;
}

void InterfaceCAN::setDonnees(UCHAR donnees)
{
    this->donnees = donnees;
}

void InterfaceCAN::afficherEvenement(t_CANevent* pEvent, HANDLE hThread, short nbEvent)
{
    QString evenement = "", tmp = "";

    tmp.sprintf("Evt[%2d] Thread[%X] ", nbEvent, hThread);
    evenement.append(tmp);

    switch(pEvent->eventType)
    {
    case _CAN_TX_DATA : evenement.append("TxD ");
        break;
    case _CAN_RX_DATA : evenement.append("RxD ");
        break;
    }

    switch(pEvent->CANerr)
    {
    case _CAN_ACTIVE_ERR : evenement.append("NORMAL ");
        break;
    }

    switch(pEvent->identType)
    {
    case _CAN_STD : evenement.append("STANDARD ID ");
        break;
    case _CAN_EXT : evenement.append("EXTEND ID ");
        break;
    }

    tmp.sprintf(" 0x%03x [%u] ", pEvent->ident, pEvent->dlc);
    evenement.append(tmp);

    if( pEvent->eventType == _CAN_RX_DATA)
    {
        for(int i = 0; i < pEvent->dlc && i <= _CAN_MAX_DATA; i++)
        {
            tmp.sprintf("%02X ", pEvent->data[i]);
            evenement.append(tmp);
        }
    }

    cout << endl << evenement.toStdString() << endl;
}

DWORD WINAPI InterfaceCAN::lireBuffer(LPVOID threadContext)
{
    short nbEvent = 0;
    LPTHREAD_PARAMS pThreadContext = reinterpret_cast<LPTHREAD_PARAMS>(threadContext);

    while(1) {

        // Si un évènement est signalé
        if(WaitForSingleObject(pThreadContext->hEvent, INFINITE) == WAIT_OBJECT_0)
        {
            t_CANevent event;

            if(Ic_GetBuf(pThreadContext->hCanal, pThreadContext->ident, &event) == _OK)
            {
                nbEvent++;
                afficherEvenement(&event, pThreadContext->hThread, nbEvent);
            }
        }
    }

    return 0;
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
