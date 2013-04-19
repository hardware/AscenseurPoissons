//    --------------------------------------------
//    Reprise du programme d'exemple d'utilisation 
//    de l'interface logicielle CAN NSI
//    --------------------------------------------
//
//            M O D E   F I F O
//
// 
// Ce programme montre comment émettre et recevoir des
// trames en mode FIFO sur une carte CAN PCI de la société NSI.

// L'émission des trames est déclenchée
// par l'appui sur des touches du clavier.
//
// La réception est réalisée par un Thread
// qui attend le remplissage de la FIFO
// pour afficher les évènements CAN.
//
//------------------------------------------------------------

#include <windows.h>
#include <conio.h>
#include <stdio.h>

// Inclusion des fichiers de déclaration des structures 
// et des fonctions de l'interface CAN pour le développement en C/C++.
// Definit la convention d'appel des fonctions de la DLL
// spécifique aux outils Microsoft

#include "canpcex.h" // contient "candefex.h" et "canproex.h"

// Prototypes des fonctions du programme d'exemple
//
#include "candemo.h"

// Variables globales
// ------------------
//
// Synchronisation de l'affichage
HANDLE hMutex;		
		
// Handle du canal ouvert
HANDLE hCanal = INVALID_HANDLE_VALUE;

// Handle de l'évènement FIFO
HANDLE hEvent = INVALID_HANDLE_VALUE;

unsigned short longdonnee = 5;

//  MAIN( )
//-----------
// Fonction principale du programme d'exemple.
void main( void ) 
{	
	// Variables internes diverses
	int	  i		= 0;
	short cr	= 0; //paramètre de retour des primitives associées à la carte
	BOOL  done	= FALSE;
	short canal	= 0;
	char  key[2];
	short DLL,DRV;
	unsigned long cardCount = 0; //compteur de canaux	
	unsigned char data[8];
	
	// Pour recevoir la description de chacun des canaux disponibles sur l'ordi
	// (MAX = 10)

	t_CardData cardData[10]; // de candefex.h
	/*Enregistrement des informations de configuration d'une carte 
	typedef struct
	{
		unsigned long IOBaseAddress;
		unsigned long memoryBaseAddress;
		unsigned long IRQLineNumber;
		unsigned long DMAChannelNumber;
		unsigned long cardAlreadyOpen;
		unsigned long boardType;
		char		  cardNameString[80];
		unsigned long reserved;
	} t_CardData; */

	// Variables de controle du Thread
	DWORD threadId;
	HANDLE hThread;
	
	// Structure d'initialisation d'un message CAN de candefex.h
	t_CANobj		canObj;

	// Structure d'initialisation du bus CAN de candefex.h
	//
	// typedef struct
	//{
	//	unsigned char	baudpresc;	// Baud Rate Prescaler
	//	unsigned char	tseg1;		// TSEG1
	//	unsigned char	tseg2;		// TSEG2
	//	unsigned char	sjw;		// Synchronization Jump Width
	//	unsigned char	sample;		// Sampling mode

	//} t_CANbusParams;
	//
	t_CANbusParams	canBus;


	hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );


	hMutex = CreateMutex( NULL, FALSE, NULL );


	hThread = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)Thread,
		hEvent,
		0,
		&threadId );
	
	// Ic_EnumCards(	unsigned long* cardcnt,
	//					t_CardData* carddata, 
	//					unsigned long carddatasz)
	// ------------
	// Lorsque plusieurs canaux CAN sont disponibles dans un même
	// PC, il est utile de connaître les particularités de chaque
	// canal pour choisir lequel utiliser. Cette fonction retourne 
	// la liste des canaux utilisables dans un tableau cardData
	// d'enregistrements de type: t_CardData. L'indice 
	// du tableau correspond au numéro du canal.
	//
	cr = Ic_EnumCards( &cardCount, cardData, sizeof( cardData ));

	Echo( "Ic_EnumCards : %s\n", GetCodeString( cr ) );
	if( cr != _OK )
	{
		Echo(" Failed to get CAN channels list." );
		getch( );
		return;
	}

	// Affiche la liste des canaux. ATTENTION : malgré le nom de cette primitive
	// ici le nombre de cartes est 
	// considéré comme équivalent au nombre de canaux et comme il y a deux canaux
	// par carte dans notre cas (carte CAN PCI 2 canaux CAN High Speed),
	// il suffit de diviser par 2 le nombre de canaux
	// obtenus pour connaître le nombre de cartes réellement installées dans l'ordi.
	
	// Cette primitive trouve également le premier 
	// canal disponible. L'index de ce canal est placé dans la 
	// variable "canal". Sinon -1 ce qui indique aucun canal libre.
	//
	Echo( "  Detected Channels : %d", cardCount ); // nombre de canaux
	Echo( "  Detected Boards : %d\n", cardCount/2 ); // nombre de cartes
	canal = -1;
	for( i=0; i<(int)cardCount; i++ )
	{
		Echo("Channel: %d - BoardType: %2d IOBaseAd:% 4Xh MemBaseAd:% 8Xh IRQ:% 2d DMACh:% 2d %s \t(%d)  [(0) if opened]\n", 
			i,
			cardData[i].boardType,
			cardData[i].IOBaseAddress,
			cardData[i].memoryBaseAddress,
			cardData[i].IRQLineNumber,
			cardData[i].DMAChannelNumber,
			cardData[i].cardNameString,
			cardData[i].cardAlreadyOpen ); // =0 (FALSE) si canal fermé
		
		// Trouve le premier canal disponible cad non utilisé au même
		// moment par une autre application.
		if( canal == -1 && cardData[i].cardAlreadyOpen == FALSE ) 
		{
			canal = i; //numéro du premier canal libre
			
		}
	}

	// Vérifie qu'au moins un canal est disponible
	if( canal < 0 )
	{
		Echo("  The application needs at least one available CAN channel..." );
		getch( );
		return;
	}

	Echo( "  \nThe first free channel is CH%d. This is this channel we'll use!!! \n", canal );

	// Ic_InitDrv(short cno, HANDLE* hdrv)
	// ----------
	// Cette primitive permet de sélectionner et d'initialiser
	// un canal CAN. Un "Handle" est retourné dans la variable "hCanal".
	// Ce "Handle" permet d'identifier et de différencier ce
	// canal afin de pouvoir éventuellement utiliser plusieurs canaux 
	// dans une même application. Cette valeur est passée à toutes
	// les autres fonctions de l'interface logicielle CAN.
	// La valeur du premier paramètre indique l'indice du canal que
	// l'on veut utiliser (ici le premier libre détecté par la primitive
	// Ic_EnumCards(). Celui-ci correspond
	// à l'indice canal=i dans le tableau de taille cardCount+1). 
	//
	cr = Ic_InitDrv( canal, &hCanal );

	Echo("Ic_InitDrv(Channel used : CH%d,\n\t\t Handler = %Xh) : %s.\n", canal, hCanal, GetCodeString( cr ));
	
	if( cr != _OK )
	{
		Echo(" Unable to select CAN channel #%d.", canal );
		getch( );
		return;
	}

	// Ic_GetAPIinfo(	HANDLE hdrv,
	//					short* DLLversion,
	//					short *DRVversion,
	//					unsigned long* reserved)
	// ---------------
	// Retourne le type de la carte du canal initialisé et les versions des 
	// fichiers de l'interface logicielle.
	//
	cr = Ic_GetAPIinfo( hCanal, &DLL, &DRV, NULL );
	Echo("Ic_GetAPIinfo(Versions : Dll:%.2f  Drv:%.2f) : %s.\n", 
		DLL / 100.0, // version DLL
		DRV / 100.0, // version Driver
		GetCodeString(cr)); 
	if( cr != _OK ) done = TRUE;

	// Ic_InitChip( HANDLE hdrv,
	//				t_CANbusParams busParams, 
	//				t_CANaddressing adressing, 
	//				t_CANpadding)
	// -----------
	// Initialise les registres : Bit Timing Register 0 et 1
	// Configuration du controleur CAN SJA1000 : 
	// débit (250kbit/s), 
	// position échantillon (75%),
	// 1 seul échantillon
	// avec :
			// Baudrate = Fclk/[2xBRPx(1+TSEG1+TSEG2)] (Fclk = 16 MHz)

	canBus.baudpresc	= 2;	// BRP	 = 2
	canBus.tseg1		= 11;	// TSEG1 = 11
	canBus.tseg2		= 4;	// TSEG2 = 4
	canBus.sjw			= 1;	// SJW	 = 1
	canBus.sample		= 0;	// SPL	 = 0 (1 échantillon)
								//		 = 1 (3 échantillons)

	// Les 2 derniers parametres sont reserves a une utilisation DiagOnCAN avec MUXy

	cr = Ic_InitChip( hCanal, canBus, _DC_NORMAL, _DC_NO_PADDING );

	Echo("Ic_InitChip (Bit Rate = 250kbit/s,\n\t\tPosition : 75%%,\n\t\t1 Synchronisation Jump Width,\n\t\t1 Sample) : %s.\n", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_InitInterface( HANDLE hdrv,t_Interface Interface )
	// ----------------
	// Initialise l'interface CAN: Le mode de gestion des évènements 
	// (FIFO ou Buffer) voir t_Interface dans candefex.h
	//
	cr = Ic_InitInterface( hCanal, _FIFO );

	Echo("Ic_InitInterface(FIFO : Les evts (en emission/recept.) sont ranges dans l'ordre d'arrivee (file d'attente)) : %s.\n", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_ConfigEvent(	HANDLE hdrv, 
	//					HANDLE hEvent, 
	//					unsigned long ident /* = 0 car mode FIFO */ )
	// -----------
	// Indique à l'interface logicielle le HANDLE associé à l'évènement devant être 
	// utilisé pour signaler les évènements concernant la FIFO.
	// Voir les
	// fonction Thread et CreateEvent..
	//
	cr = Ic_ConfigEvent( hCanal, hEvent, 0 );

	Echo( "Ic_ConfigEvent( ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Déclaration d'une trame de données en émission portant l'ident 
	// CAN_IDENT avec demande d'acquittement. Dans un premier temps, 
	// on initialise la structure 'canObj' contenant les informations 
	// du message CAN.
	// ------------------------------------------------------------------
	//
	// Valeur de l'identificateur du message compris entre 
	// 0x000 et 0x7FF pour un 
	// format de trame STD.
	canObj.ident = CAN_IDENT;

	// Format de trame :	_CAN_STD = 0,		/* Standard 11 bits */
	//						_CAN_EXT = 1,		/* Extended 29 bits */
	//						_CAN_ALL = 2	les 2 formats sont 
											//utilisables
	canObj.identType = _CAN_STD;

	// Type du message CAN : trame d'émission de données
	canObj.frameType = _CAN_TX_DATA;

	// Taille de la zone de données du message en octets 0 à 8
	canObj.dlc = 5;	

	// Demande de compte rendu pour ce message. En mode FIFO, ce 
	// paramètre est indispensable pour que le compte rendu de
	// l'échange soit placé dans la FIFO.
	canObj.statusRq = _STATUS;

	// Valeurs des 5 octets de données
	canObj.data[0] = 0x01;
	canObj.data[1] = 0x02;
	canObj.data[2] = 0x03;
	canObj.data[3] = 0x04;
	canObj.data[4] = 0x05;
	
	// Ic_InitId( HANDLE hdrv,t_CANobj* msg)
	// ---------
	// Déclare l'identificateur du message CAN dont les données 
	// sont précisées dans 
	// la structure pointée par canObj.
	cr = Ic_InitId( hCanal, &canObj );
	
	Echo( "Ic_InitId( %03Xh,%d,TX_DATA ) : %s.", canObj.ident, canObj.dlc, GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_SetRxMask(	HANDLE hdrv,
	//					unsigned long code, 
	//					unsigned long mask, 
	//					t_CANidentType identType)
	// ------------
	// Déclare la réception des trames de données d'un groupe 
	// d'identificateur définis par un masque de bits. Dans cet
	// exemple, on ne recoit que les identificateurs STD pairs.

	cr = Ic_SetRxMask( hCanal, 0x000, 0x001, _CAN_STD );

	Echo( "Ic_SetRxMask( Mask=0x001, Val=0x000 ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_StartChip( HANDLE hdrv)
	// ------------
	// Démarre le controleur CAN. Les réceptions, démarrent à cet instant.
	// Le controleur acquitte les trames correctement formatées qui 
	// circulent sur le réseau.
	//
	cr = Ic_StartChip( hCanal );
	Echo( "Ic_StartChip : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Test : initialisation et démarrage du canal CAN
	// réussis ? En cas d'échec, le programme est arrêté.
	//
	if( done )
	{
		Echo( " Failed to initialize CAN interface. Program will stop." );
	}
	else
	{
		Echo( " " );
		Echo( " Press [A] key to transmit ID %03Xh ", CAN_IDENT );
		Echo( " Press [ESC] three times to Exit program " );
	}

	key[1] = 0;

	memset( data, 0x00, sizeof(data) );
	
	// Boucle tant que la touche ESC n'est pas pressée.
	//	
	while( !done )
	{
		key[0] = getch( );
		strupr( key );
		switch( key[0] )
		{
		case 'A' :

			// Prépare les données à transmettre dans le message
			//
			for( i=0; i<longdonnee; i++ ) 
			{
				data[i]=canObj.data[i];
			};

			// Ic_TxMsg(	HANDLE hdrv,
			//				unsigned long ident, 
			//				unsigned short dlc, 
			//				unsigned char *data)
			// --------
			// Met a jour les données et active la transmission du message 
			// portant l'identificateur passés en paramètre.
			//			
			cr = Ic_TxMsg( hCanal, CAN_IDENT, longdonnee, data );
	
			Echo( "Ic_TxMsg( %03Xh,%d,data ) : %s", CAN_IDENT,longdonnee, GetCodeString( cr ));
			break;

		case (char)27 : // code ASCII de la touche ESC
			// Indique que la boucle while doit se terminer
			done = TRUE;
			break;

		default :			
			Echo( "Type [A] ActiveID or three times [ESC] to Exit" );
		}
	}

	// Ic_ExitDrv( HANDLE hdrv)
	// ----------
	// Ferme le handle du canal et libère le canal pour que d'autres
	// applications puissent l'utiliser
	//
	cr = Ic_ExitDrv( hCanal );
	
	Echo( "Ic_ExitDrv : %s", GetCodeString(cr));

	// Arrête l'éxecution du Thread.
	TerminateThread( hThread, 0 );

	// Libere les ressources système
	if( hEvent ) CloseHandle( hEvent );
	if( hMutex ) CloseHandle( hMutex );
	puts(" Done : Press Key...");
 	getch( );

	// Fin du programme principal
}


// Thread
// ------
// La fonction Thread est créé par le programme principal. 
// Elle s'éxécute en parallèle et de manière asynchrone.
// Elle attend que la FIFO passe de l'état VIDE à NON VIDE. 
// Ceci est signalé par un évènement "event".
// Le thread attend  que l'"event" soit signalé pour 
// dépiler le ou les évènements présents dans la FIFO. Le 
// HANDLE de l'évènementt est passé en paramètre à la fonction du 
// Thread. Ce thread est arrêté par le Thread principal 
// lorsqu'il se termine.
//
DWORD Thread( HANDLE hEvent )
{
	t_CANevent event;
	long count = 0;
	char string[0x100];

	// Boucle "infinie" (tant que le thread principal fonctionne)
	while( 1 )
	{
		// Cette fonction place le thread en attente de l'évènement.
		// Noter que ceci n'occupe plus de temps CPU. Le thread est
		// endormi jusqu'à ce que le système le réveille lorsque 
		// l'évènement "hEvent" est signalé.
		//
		if( WaitForSingleObject( hEvent, INFINITE ) == WAIT_OBJECT_0 )
		{
			// Boucle tant que des évènement sont dépilé de la FIFO
			while( Ic_GetEvent( hCanal, &event ) == _OK )
			{	
				count++;
				// Affiche une ligne de texte décrivant l'évènement
				GetEventString( &event, string );				
				Echo( " Evt% 4d %s", count, string );
			}
		}
	}	
	return 0;
}

//-----------------------------------------------------
// Fonctions diverses utilisée par le programme de test
// Versatile functions used by the test program
//-----------------------------------------------------

// Echo
// ----
// Cette fonction correspond à "printf" mais avec une protection
// contre les accès simultanés a l'affichage. En effet, le Thread et
// le programme principal peuvent acceder simultanément à l'écran 
// ce qui peut provoquer affichages erronés.
//
void __cdecl Echo( const char* format, ... )
{	
	FILE str;
	va_list list;
	char buffer[0x1000];

	va_start( list, format );
	memset( buffer, 0x00, sizeof( buffer ));

	str._flag = _IOWRT|_IOSTRG;
    str._ptr = str._base = buffer;
    str._cnt = sizeof( buffer );
    _output( &str,format,list);

	// Synchronise les accès a l'écran par différent Threads
	WaitForSingleObject( hMutex, INFINITE );
	puts( buffer );
	ReleaseMutex( hMutex );
}

// GetCodeString
// -------------
// Retourne le nom explicite du code erreur passé en paramètre
//
char* GetCodeString( short cr )
{
	switch( cr )
	{
	case _OK :					return "_OK";
	case _MEM_ERR :				return "_MEM_ERR";
	case _SEQ_ERR :				return "_SEQ_ERR";
	case _PARAM_ERR :			return "_PARAM_ERR";
	case _CHIP_ERR :			return "_CHIP_ERR";
	case _BOARD_ERR :			return "_BOARD_ERR";
	case _ID_OVERFLOW :			return "_ID_OVERFLOW";
	case _UNKNOWN_ID :			return "_UNKNOWN_ID";
	case _UNKNOWN_PERIOD :		return "_UNKNOWN_PERIOD";
	case _PERIODIC_OVERFLOW :	return "_PERIODIC_OVERFLOW";
	case _EMPTY_BUF :			return "_EMPTY_BUF";
	case _EMPTY_FIFO :			return "_EMPTY_FIFO";
	case _FRAME_TYPE_ERR :		return "_FRAME_TYPE_ERR";
	case _INTERFACE_ERR :		return "_INTERFACE_ERR";
	case _BUF_OCCUPIED :		return "_BUF_OCCUPIED";
	case _INVALID_OP :			return "_INVALID_OP";
	case _DRV_PARAM_ERR :		return "_DRV_PARAM_ERR";
	case _OPENING_DRV_ERR :		return "_OPENING_DRV_ERR";
	case _SLEEP_MODE :			return "_SLEEP_MODE";
	case _USB_ERR :				return "_USB_ERR";
	case _RS232_ERR :			return "_RS232_ERR";
	case _BOARD_TIMEOUT :		return "_BOARD_TIMEOUT";
	default :					return "_???";
	}
}

// GetBoardTypeString
// ------------------
// Retourne le nom explicite du type de la carte passé en paramètre
//
char* GetBoardTypeString( unsigned long type )
{
	switch( type )
	{
	case _CANPC :				return "CANPC";
	case _CANPC_OPTO :			return "CANPC/OP";
	case _CANPCA :				return "CANPCa";
	case _CANPCA_LS :			return "CANPCa/LS";
	case _CANPCA_OPTO :			return "CANPCa/OP";
	case _CANPCMCIA :			return "CANPCMCIA";
	case _CANPCMCIA_LS :		return "CANPCMCIA/LS";
	case _CANPCMCIA_OPTO :		return "CANPCMCIA/OP";
	case _CANPCI :				return "CANPCI";
	case _CANPCI_LS :			return "CANPCI/LS";
	case _CANPCI_OPTO :			return "CANPCI/OP";
	case _CANUSB :				return "CAN-USB";
	case _CAN_OBDUSB :			return "MUXy";
	case _CANEX_OBDUSB :		return "MUXy (ISO 15765-2)";
	case _MUXYBOX :				return "MUXy box";
	case _MUXYBOX_KWPTEST :		return "MUXy box (KWP_Test)";
	case _MUXYLIGHT	:			return "MUXy light";
	default :					return "BOARD ???";
	}
}


// GetEventString
// --------------
// Cette fonction retourne une ligne de texte formaté décrivant les 
// paramètres principaux de l'event pointé par "pEvent". "string" doit 
// pointer sur un buffer suffisamment grand pour contenir le texte.
//
void GetEventString( t_CANevent* pEvent, char* string )
{
	int i;
	char tmp[80];

	memset( tmp,0x00,sizeof(tmp));
	*string = (char)NULL;

	// Affiche le type de l'évènement
	switch( pEvent->eventType )
	{ 
	case _CAN_TX_DATA : strcat( string, "TXD " );
	break;
	case _CAN_RX_DATA : strcat( string, "RXD " );
	break;
	case _CAN_TX_RX_REMOTE : strcat( string, "TRR " );
	break;
	case _CAN_TX_REMOTE : strcat( string, "TXR " );
	break;
	case _CAN_RX_REMOTE : strcat( string, "RXR " );
	break;
	case _CAN_RX_DATA_REMOTE : strcat( string, "RDR " );
	break;
	case _CAN_TX_AUTO_REMOTE : strcat( string, "TAR " );
	break;
	default : strcat( string, "??? " );				
	}

	// Affiche la valeur de l'identificateur et la taille de la trame
	sprintf( tmp, " %03xh [% 2d] ", pEvent->ident, pEvent->dlc );
	strcat( string, tmp );	

	// Affiche les octets de donnée
	if( pEvent->eventType == _CAN_RX_DATA ||
		pEvent->eventType == _CAN_RX_DATA_REMOTE )
	{
		for( i=0; i<pEvent->dlc && i<=_CAN_MAX_DATA; i++ )
		{
			sprintf( tmp, "%02x ", pEvent->data[i] );
			strcat( string, tmp );
		}
	}
}


