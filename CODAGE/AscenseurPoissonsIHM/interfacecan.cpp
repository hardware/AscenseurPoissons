#include "interfacecan.h"

/**
 * @brief Constructeur par défaut
 *
 * Permet d'allouer dynamiquement un tableau
 * de structures contenant les paramètres des threads.
 */
InterfaceCAN::InterfaceCAN()
{
    idCanal     = INVALID_HANDLE_VALUE;
    indexThread = 1;

    for(int i = 0; i < NB_MAX_THREADS; i++)
        pThreadContext[i] = (LPTHREAD_PARAMS)malloc(sizeof(THREAD_PARAMS));
}

/**
 * @brief Destructeur par défaut
 *
 * Permet de libérer la zone mémoire allouée prédécement
 * par malloc puis invalide le pointeur.
 */
InterfaceCAN::~InterfaceCAN()
{
    for(int i = 0; i < NB_MAX_THREADS; i++)
    {
        free(pThreadContext[i]);
        pThreadContext[i] = NULL;
    }
}

/**
 * @fn void InterfaceCAN::ouvrirCanal(short indexCanal)
 * @brief Permet d'ouvrir un canal CAN
 *
 * Une fois la primitive Ic_InitDrv exécutée, l'attribut idCanal
 * est initialisé avec l'identificateur du canal.
 *
 * Plusieurs canaux peuvent être ouverts par la même application,
 * par contre un même canal ne peut pas être ouvert simultanément
 * par deux applications.
 *
 * @param[in] indexCanal Numero du canal à ouvrir
 */
void InterfaceCAN::ouvrirCanal(short indexCanal)
{
    val = Ic_InitDrv(indexCanal, &idCanal);

    if(val != _OK)
        throw string("Ic_InitDrv : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::fermerCanal()
 * @brief Permet de fermer le canal CAN précédement ouvert
 *
 * Permet de libérer le canal afin que d'autres applications
 * puissent l'utiliser.
 */
void InterfaceCAN::fermerCanal()
{
    val = Ic_ExitDrv(idCanal);

    if(val != _OK)
        throw string("Ic_ExitDrv : " + getCode(val));
}

/**
 * @fn short InterfaceCAN::listeCanaux()
 * @brief Permet de lister les canaux disponibles
 *
 * Permet d'afficher la liste des canaux présents sur la carte
 * avec le statut (libre/utilisé) à côté.
 *
 * @return Retourne le nombre de canaux disponibles sur la carte
 */
short InterfaceCAN::listeCanaux()
{
    t_CardData donneeCarte[10];
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

/**
 * @fn void InterfaceCAN::getInfos()
 * @brief Affiche diverses informations sur le périphérique
 *
 * Affiche le type de la carte du canal initialisé et les
 * version des fichiers de l'interface logicielle.
 */
void InterfaceCAN::getInfos()
{
    short DLL, DRV;
    t_CANdeviceInfo infosCarte;

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

/**
 * @fn void InterfaceCAN::initialiserControleur()
 * @brief Permet d'initialiser le contrôleur de protocole CAN
 *
 * Cette méthode permet de configurer les paramètres du bus CAN.
 * Le débit est fixé à 250 kBits/s avec un point d'échantillonnage à
 * 75% avec 1 échantillon.
 */
void InterfaceCAN::initialiserControleur()
{
    t_CANbusParams parametresBUS;

    parametresBUS.baudpresc = 2;  // BRP
    parametresBUS.tseg1     = 11; // Segment précédent le point d'échantillonnage
    parametresBUS.tseg2     = 4;  // Segment suivant le point d'échantillonnage
    parametresBUS.sjw       = 1;  // Synchronisation Jump Width
    parametresBUS.sample    = 0;  // 0 pour 1 échantillon et 1 pour 3 échantillons

    val = Ic_InitChip(idCanal, parametresBUS, _DC_EXTENDED, _DC_NO_PADDING);

    if(val != _OK)
        throw string("Ic_InitChip : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::initialiserModeFonctionnement()
 * @brief Permet d'initialiser le mode de fonctionnement de l'interface CAN
 *
 * Cette méthode permet d'initialiser l'interface CAN en mode BUFFER
 * afin de mémoriser les évènements (réception d'une trame) pour
 * chaque identificateur déclaré avec Ic_InitId.
 */
void InterfaceCAN::initialiserModeFonctionnement()
{
    val = Ic_InitInterface(idCanal, _BUFFER);

    if(val != _OK)
        throw string("Ic_InitInterface : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::initialiserIdentificateur(t_CANframeType typeTrame, t_identTrame ident, USHORT dlc)
 * @brief Permet de déclarer un identificateur CAN
 *
 * Dans notre cas, nous avons besoin de déclarer 5 identificateurs :
 *
 * [COFFRET PECHEUR]
 * - Une trame en émission  RxPDO1 pour les sorties TOR         (COB-ID = 0x210) (DLC = 2 octets)
 * - Une trame en réception TxPDO1 pour les entrées TOR         (COB-ID = 0x190)
 * - Une trame en réception TxPDO2 pour les entrées analogiques (COB-ID = 0x290)
 *
 * [SOMMET ASCENSEUR]
 * - Une trame en émission  RxPDO1 pour les sorties TOR         (COB-ID = 0x220) (DLC = 1 octet)
 * - Une trame en réception TxPDO1 pour les entrées TOR         (COB-ID = 0x200)
 *
 * @param typeTrame[in] Type de trame (TxD, RxD, ...etc)
 * @param ident[in]     Identificateur CAN du message
 * @param dlc[in]       Nombre d'octets de la zone données à initialiser.
 */
void InterfaceCAN::initialiserIdentificateur(t_CANframeType typeTrame, t_identTrame ident, USHORT dlc)
{
    t_CANobj messageCAN;

    messageCAN.ident     = ident;
    messageCAN.identType = _CAN_STD;
    messageCAN.frameType = typeTrame;
    messageCAN.dlc       = dlc;

    val = Ic_InitId(idCanal, &messageCAN);

    if(val != _OK)
        throw string("Ic_InitId : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::initialiserMasque()
 * @brief Permet de définir le masque de réception
 *
 * Cette méthode permet de configurer et d'active le buffer de réception global (buffer 64)
 * permettant de recevoir les messages d'identificateurs non déclarés.
 */
void InterfaceCAN::initialiserMasque()
{
    val = Ic_SetRxMask(idCanal, 0x000, 0x001, _CAN_STD);

    if(val != _OK)
        throw string("Ic_SetRxMask : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::initialiserEvenementGlobal()
 * @brief Permet d'initialiser l'évènement signalant le changement
 * d'état du buffer de réception global
 *
 * Cette méthode initialise tout d'abord les paramètres du thread
 * qui permet de lire dans le buffer 64 afin de récupérer les
 * données reçues.
 *
 * L'évènement est créée avec la fonction CreateEvent de l'API win32
 *
 * Ensuite on indique à l'interface logicielle le HANDLE de l'évènement
 * système pour signaler le changement d'état du buffer 64.
 * L'évènement est "signalé" lorsque le buffer passe de l'état "vide" à "non-vide"
 */
void InterfaceCAN::initialiserEvenementGlobal()
{
    pThreadContext[0]->ident  = _CAN_DUMMY_ID;
    pThreadContext[0]->hCanal = idCanal;
    pThreadContext[0]->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    if(pThreadContext[0]->hEvent == NULL)
        throw string("Une erreur est survenue lors de la creation de l evenement associe au thread 0");

    val = Ic_ConfigEvent(idCanal, pThreadContext[0]->hEvent, _CAN_DUMMY_ID);

    if(val != _OK)
        throw string("Ic_ConfigEvent Thread[0] : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::initialiserEvenement(t_identTrame ident)
 * @brief Permet d'initialiser un évènement signalant le changement
 * d'état du buffer de l'identificateur passé en paramètre
 *
 * Cette méthode initialise tout d'abord les paramètres du thread
 * qui permet de lire dans le buffer de l'identificateur
 * passé en paramètre
 *
 * Ensuite on indique à l'interface logicielle le HANDLE de l'évènement
 * système pour signaler le changement d'état du buffer.
 *
 * @param ident[in] Identificateur CAN
 */
void InterfaceCAN::initialiserEvenement(t_identTrame ident)
{
    pThreadContext[indexThread]->ident  = ident;
    pThreadContext[indexThread]->hCanal = idCanal;
    pThreadContext[indexThread]->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    if(pThreadContext[indexThread]->hEvent == NULL)
        throw string("Une erreur est survenue lors de la creation de l evenement associe au thread " + indexThread);

    val = Ic_ConfigEvent(idCanal, pThreadContext[indexThread]->hEvent, ident);

    if(val != _OK)
        throw string("Ic_ConfigEvent Thread[X] : " + getCode(val));

    indexThread++;
}

/**
 * @fn void InterfaceCAN::demarrerControleur()
 * @brief Permet de démarrer le contrôleur CAN
 *
 * Une fois le contrôleur démarré, il est capable d'envoyer et
 * de recevoir des trames sur bus. Tous les identificateurs déclarés
 * en réception sont automatiquement validés et activés et ceux en émission
 * sont validés.
 */
void InterfaceCAN::demarrerControleur()
{
    val = Ic_StartChip(idCanal);

    if(val != _OK)
        throw string("Ic_StartChip : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::arreterControleur()
 * @brief Permet d'arrêter le contrôleur CAN
 *
 * Le contrôleur CAN est placé en mode initialisation et n'est plus
 * connecté au bus.
 */
void InterfaceCAN::arreterControleur()
{
    val = Ic_StopChip(idCanal);

    if(val != _OK)
        throw string("Ic_StopChip : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::ecrireDonneeSommetAscenseur(UCHAR donnees)
 * @brief Permet de mettre à jour les données des sorties TOR du sommet ascenseur
 *
 * Active l'identificateur en émission puis transmet le
 * message sur le bus.
 *
 * @param donnees[in] Données à mettre à jour
 */
void InterfaceCAN::ecrireDonneeSommetAscenseur(UCHAR donnees)
{
    val = Ic_TxMsg(idCanal, _SORTIESTOR_SOMMET_ID, sizeof(donnees), &donnees);

    if(val != _OK)
        throw string("Ic_TxMsg : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::ecrireDonneeCoffretPecheur(UCHAR donnees)
 * @brief Permet de mettre à jour les données des sorties TOR du coffret pécheur
 *
 * Active l'identificateur en émission puis transmet le
 * message sur le bus.
 *
 * @param donnees[in] Données à mettre à jour
 */
void InterfaceCAN::ecrireDonneeCoffretPecheur(UCHAR donnees)
{
    val = Ic_TxMsg(idCanal, _SORTIESTOR_COFFRET_ID, sizeof(donnees), &donnees);

    if(val != _OK)
        throw string("Ic_TxMsg : " + getCode(val));
}

/**
 * @fn void InterfaceCAN::demarrerThread()
 * @brief Permet de créer les threads de lecture du buffer
 *
 * Actuellement le programme crée 3 threads pour la réception
 * des données des buffers liés aux identificateurs déclarés
 * en réception. Ainsi qu'un autre pour la lecture du buffer
 * de réception global.
 *
 * Les threads sont crées avec la fonction CreateThread de l'API win32.
 *
 * Les paramètres des threads sont contenus dans une structure
 * de type LPTHREAD_PARAMS.
 */
void InterfaceCAN::demarrerThread()
{
    for(int i = 0; i < NB_MAX_THREADS; i++)
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
            throw string("Une erreur est survenue lors de la creation des threads");
    }
}

/**
 * @fn void InterfaceCAN::interrompreThread()
 * @brief Permet d'interrompre les threads
 *
 * Les threads sont interrompus avec la fonction TerminateThread et
 * les évènements sont fermés avec la fonction CloseHandle de
 * l'API win32.
 *
 * Attention : Il est nécessaire de contrôler que le thread ne fait
 * plus appel au pilote du périphérique car ça pourrait nuire à la
 * stabilité du système d'exploitation.
 */
void InterfaceCAN::interrompreThread()
{
    for(int i = 0; i < NB_MAX_THREADS; i++)
    {
        if(pThreadContext[i]->hThread)
            TerminateThread(pThreadContext[i]->hThread, 0);

        if(pThreadContext[i]->hEvent)
            CloseHandle(pThreadContext[i]->hEvent);
    }
}

/**
 * @fn void InterfaceCAN::afficherEvenement(t_CANevent* pEvent, HANDLE hThread, short nbEvent)
 * @brief Affiche des données d'un évènement
 *
 * Cette méthode permet d'afficher les données d'une trame en réception.
 *
 * @param pEvent[in]  Pointeur sur l'évènement à traiter
 * @param hThread[in] Identificateur du thread
 * @param nbEvent[in] Numéro de l'évènement
 */
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

/**
 * @fn DWORD WINAPI InterfaceCAN::lireBuffer(LPVOID threadContext)
 * @brief Permet de lire dans le buffer
 *
 * Cette méthode est la fonction exécutée par les threads
 * de l'application qui s'exécuteront en parallèle et de
 * manière asynchrone. Le prototype de cette méthode est
 * imposé par l'API win32 et doit être définit comme ceci :
 *
 * DWORD WINAPI Fonction(LPVOID threadParams);
 *
 * Le thread attend que l'évènement soit signalé pour
 * lire les données contenues dans le BUFFER. Le HANDLE de
 * l'évènement et du canal, ainsi que la valeur des
 * identificateurs déclarés sont passés en paramètre
 * à la fonction du thread dans la structure threadContext.
 *
 * Cette méthode doit être obligatoirement déclarée avec
 * la directive "static" sinon le cast vers le type
 * LPTHREAD_START_ROUTINE ne peut pas être appliqué.
 *
 * @param threadContext[in] Paramètres du thread
 */
DWORD WINAPI InterfaceCAN::lireBuffer(LPVOID threadContext)
{
    short nbEvent = 0;

    /*
     Le paramètre d'une fonction représentant un thread
     doit être obligatoirement de type LPVOID. Donc pour
     avoir accès aux champs de la structure threadContext,
     on doit réappliquer le type d'origine (LPTHREAD_PARAMS)
     avec reinterpret_cast (ou static_cast)
    */
    LPTHREAD_PARAMS pThreadContext = reinterpret_cast<LPTHREAD_PARAMS>(threadContext);

    // Boucle "infinie" (tant que le thread principal fonctionne)
    while(1) {

        /*
         Cette fonction place le thread en attente de l'évènement.
         Le thread n'occupe plus de temps CPU, il est endormi
         jusqu'à que le système le réveille lorsque l'évènement
         est signalé (WAIT_OBJECT_0)
        */
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

/**
 * @fn void InterfaceCAN::lireEtat(t_identTrame ident)
 * @brief Permet d'aller chercher les données des entrées TOR
 *
 * @param ident[in] Identificateur CAN
 */
void InterfaceCAN::lireEtat(t_identTrame ident)
{
    t_CANevent event;
    QString dataString = "", tmp = "";

    val = Ic_GetBuf(idCanal, ident, &event);

    if(val != _OK)
        throw string("Ic_GetBuf : " + getCode(val));
    else
    {
        if(event.eventType == _CAN_RX_DATA)
        {
            switch(ident)
            {
            case _ENTREESTOR_COFFRET_ID : dataString.append("[COFFRET PECHEUR] ");
                break;
            case _ENTREESTOR_SOMMET_ID :  dataString.append("[SOMMET ASCENSEUR] ");
                break;
            }

            tmp.sprintf("RxD 0x%03x [%u] ", ident, event.dlc);
            dataString.append(tmp);

            for(int i = 0; i < event.dlc && i <= _CAN_MAX_DATA; i++)
            {
                tmp.sprintf("%02X ", event.data[i]);
                dataString.append(tmp);
            }

            cout << endl << dataString.toStdString() << endl;
        }
    }
}

/**
 * @fn void InterfaceCAN::lireValeur()
 * @brief Permet d'aller chercher les données des capteurs analogiques
 */
void InterfaceCAN::lireValeur()
{
    t_CANevent event;
    QString dataString = "", tmp = "";

    val = Ic_GetBuf(idCanal, _CAPTEURS_COFFRET_ID, &event);

    if(val != _OK)
        throw string("Ic_GetBuf : " + getCode(val));
    else
    {
        if(event.eventType == _CAN_RX_DATA)
        {
            dataString.append("[CAPTEURS] ");
            tmp.sprintf("RxD 0x%03x [%u] ", _CAPTEURS_COFFRET_ID, event.dlc);
            dataString.append(tmp);

            for(int i = 0; i < event.dlc && i <= _CAN_MAX_DATA; i++)
            {
                tmp.sprintf("%02X ", event.data[i]);
                dataString.append(tmp);
            }

            cout << endl << dataString.toStdString() << endl;
        }
    }
}

/**
 * @fn string InterfaceCAN::getCode(short val)
 * @brief Retourne le nom explicite du code erreur passé en paramètre
 *
 * @param val[in] Code de retour des primitives de l'interface logicielle
 * @return Retourne le nom de l'erreur
 */
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
