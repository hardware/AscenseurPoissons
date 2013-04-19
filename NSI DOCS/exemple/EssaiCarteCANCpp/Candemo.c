//    --------------------------------------------
//    Reprise du programme d'exemple d'utilisation 
//    de l'interface logicielle CAN NSI
//    --------------------------------------------
//
//            M O D E   F I F O
//
// 
// Ce programme montre comment �mettre et recevoir des
// trames en mode FIFO sur une carte CAN PCI de la soci�t� NSI.

// L'�mission des trames est d�clench�e
// par l'appui sur des touches du clavier.
//
// La r�ception est r�alis�e par un Thread
// qui attend le remplissage de la FIFO
// pour afficher les �v�nements CAN.
//
//------------------------------------------------------------

#include <windows.h>
#include <conio.h>
#include <stdio.h>

// Inclusion des fichiers de d�claration des structures 
// et des fonctions de l'interface CAN pour le d�veloppement en C/C++.
// Definit la convention d'appel des fonctions de la DLL
// sp�cifique aux outils Microsoft

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

// Handle de l'�v�nement FIFO
HANDLE hEvent = INVALID_HANDLE_VALUE;

unsigned short longdonnee = 5;

//  MAIN( )
//-----------
// Fonction principale du programme d'exemple.
void main( void ) 
{	
	// Variables internes diverses
	int	  i		= 0;
	short cr	= 0; //param�tre de retour des primitives associ�es � la carte
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
	// Lorsque plusieurs canaux CAN sont disponibles dans un m�me
	// PC, il est utile de conna�tre les particularit�s de chaque
	// canal pour choisir lequel utiliser. Cette fonction retourne 
	// la liste des canaux utilisables dans un tableau cardData
	// d'enregistrements de type: t_CardData. L'indice 
	// du tableau correspond au num�ro du canal.
	//
	cr = Ic_EnumCards( &cardCount, cardData, sizeof( cardData ));

	Echo( "Ic_EnumCards : %s\n", GetCodeString( cr ) );
	if( cr != _OK )
	{
		Echo(" Failed to get CAN channels list." );
		getch( );
		return;
	}

	// Affiche la liste des canaux. ATTENTION : malgr� le nom de cette primitive
	// ici le nombre de cartes est 
	// consid�r� comme �quivalent au nombre de canaux et comme il y a deux canaux
	// par carte dans notre cas (carte CAN PCI 2 canaux CAN High Speed),
	// il suffit de diviser par 2 le nombre de canaux
	// obtenus pour conna�tre le nombre de cartes r�ellement install�es dans l'ordi.
	
	// Cette primitive trouve �galement le premier 
	// canal disponible. L'index de ce canal est plac� dans la 
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
			cardData[i].cardAlreadyOpen ); // =0 (FALSE) si canal ferm�
		
		// Trouve le premier canal disponible cad non utilis� au m�me
		// moment par une autre application.
		if( canal == -1 && cardData[i].cardAlreadyOpen == FALSE ) 
		{
			canal = i; //num�ro du premier canal libre
			
		}
	}

	// V�rifie qu'au moins un canal est disponible
	if( canal < 0 )
	{
		Echo("  The application needs at least one available CAN channel..." );
		getch( );
		return;
	}

	Echo( "  \nThe first free channel is CH%d. This is this channel we'll use!!! \n", canal );

	// Ic_InitDrv(short cno, HANDLE* hdrv)
	// ----------
	// Cette primitive permet de s�lectionner et d'initialiser
	// un canal CAN. Un "Handle" est retourn� dans la variable "hCanal".
	// Ce "Handle" permet d'identifier et de diff�rencier ce
	// canal afin de pouvoir �ventuellement utiliser plusieurs canaux 
	// dans une m�me application. Cette valeur est pass�e � toutes
	// les autres fonctions de l'interface logicielle CAN.
	// La valeur du premier param�tre indique l'indice du canal que
	// l'on veut utiliser (ici le premier libre d�tect� par la primitive
	// Ic_EnumCards(). Celui-ci correspond
	// � l'indice canal=i dans le tableau de taille cardCount+1). 
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
	// Retourne le type de la carte du canal initialis� et les versions des 
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
	// d�bit (250kbit/s), 
	// position �chantillon (75%),
	// 1 seul �chantillon
	// avec :
			// Baudrate = Fclk/[2xBRPx(1+TSEG1+TSEG2)] (Fclk = 16 MHz)

	canBus.baudpresc	= 2;	// BRP	 = 2
	canBus.tseg1		= 11;	// TSEG1 = 11
	canBus.tseg2		= 4;	// TSEG2 = 4
	canBus.sjw			= 1;	// SJW	 = 1
	canBus.sample		= 0;	// SPL	 = 0 (1 �chantillon)
								//		 = 1 (3 �chantillons)

	// Les 2 derniers parametres sont reserves a une utilisation DiagOnCAN avec MUXy

	cr = Ic_InitChip( hCanal, canBus, _DC_NORMAL, _DC_NO_PADDING );

	Echo("Ic_InitChip (Bit Rate = 250kbit/s,\n\t\tPosition : 75%%,\n\t\t1 Synchronisation Jump Width,\n\t\t1 Sample) : %s.\n", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_InitInterface( HANDLE hdrv,t_Interface Interface )
	// ----------------
	// Initialise l'interface CAN: Le mode de gestion des �v�nements 
	// (FIFO ou Buffer) voir t_Interface dans candefex.h
	//
	cr = Ic_InitInterface( hCanal, _FIFO );

	Echo("Ic_InitInterface(FIFO : Les evts (en emission/recept.) sont ranges dans l'ordre d'arrivee (file d'attente)) : %s.\n", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_ConfigEvent(	HANDLE hdrv, 
	//					HANDLE hEvent, 
	//					unsigned long ident /* = 0 car mode FIFO */ )
	// -----------
	// Indique � l'interface logicielle le HANDLE associ� � l'�v�nement devant �tre 
	// utilis� pour signaler les �v�nements concernant la FIFO.
	// Voir les
	// fonction Thread et CreateEvent..
	//
	cr = Ic_ConfigEvent( hCanal, hEvent, 0 );

	Echo( "Ic_ConfigEvent( ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// D�claration d'une trame de donn�es en �mission portant l'ident 
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

	// Type du message CAN : trame d'�mission de donn�es
	canObj.frameType = _CAN_TX_DATA;

	// Taille de la zone de donn�es du message en octets 0 � 8
	canObj.dlc = 5;	

	// Demande de compte rendu pour ce message. En mode FIFO, ce 
	// param�tre est indispensable pour que le compte rendu de
	// l'�change soit plac� dans la FIFO.
	canObj.statusRq = _STATUS;

	// Valeurs des 5 octets de donn�es
	canObj.data[0] = 0x01;
	canObj.data[1] = 0x02;
	canObj.data[2] = 0x03;
	canObj.data[3] = 0x04;
	canObj.data[4] = 0x05;
	
	// Ic_InitId( HANDLE hdrv,t_CANobj* msg)
	// ---------
	// D�clare l'identificateur du message CAN dont les donn�es 
	// sont pr�cis�es dans 
	// la structure point�e par canObj.
	cr = Ic_InitId( hCanal, &canObj );
	
	Echo( "Ic_InitId( %03Xh,%d,TX_DATA ) : %s.", canObj.ident, canObj.dlc, GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_SetRxMask(	HANDLE hdrv,
	//					unsigned long code, 
	//					unsigned long mask, 
	//					t_CANidentType identType)
	// ------------
	// D�clare la r�ception des trames de donn�es d'un groupe 
	// d'identificateur d�finis par un masque de bits. Dans cet
	// exemple, on ne recoit que les identificateurs STD pairs.

	cr = Ic_SetRxMask( hCanal, 0x000, 0x001, _CAN_STD );

	Echo( "Ic_SetRxMask( Mask=0x001, Val=0x000 ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_StartChip( HANDLE hdrv)
	// ------------
	// D�marre le controleur CAN. Les r�ceptions, d�marrent � cet instant.
	// Le controleur acquitte les trames correctement format�es qui 
	// circulent sur le r�seau.
	//
	cr = Ic_StartChip( hCanal );
	Echo( "Ic_StartChip : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Test : initialisation et d�marrage du canal CAN
	// r�ussis ? En cas d'�chec, le programme est arr�t�.
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
	
	// Boucle tant que la touche ESC n'est pas press�e.
	//	
	while( !done )
	{
		key[0] = getch( );
		strupr( key );
		switch( key[0] )
		{
		case 'A' :

			// Pr�pare les donn�es � transmettre dans le message
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
			// Met a jour les donn�es et active la transmission du message 
			// portant l'identificateur pass�s en param�tre.
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
	// Ferme le handle du canal et lib�re le canal pour que d'autres
	// applications puissent l'utiliser
	//
	cr = Ic_ExitDrv( hCanal );
	
	Echo( "Ic_ExitDrv : %s", GetCodeString(cr));

	// Arr�te l'�xecution du Thread.
	TerminateThread( hThread, 0 );

	// Libere les ressources syst�me
	if( hEvent ) CloseHandle( hEvent );
	if( hMutex ) CloseHandle( hMutex );
	puts(" Done : Press Key...");
 	getch( );

	// Fin du programme principal
}


// Thread
// ------
// La fonction Thread est cr�� par le programme principal. 
// Elle s'�x�cute en parall�le et de mani�re asynchrone.
// Elle attend que la FIFO passe de l'�tat VIDE � NON VIDE. 
// Ceci est signal� par un �v�nement "event".
// Le thread attend  que l'"event" soit signal� pour 
// d�piler le ou les �v�nements pr�sents dans la FIFO. Le 
// HANDLE de l'�v�nementt est pass� en param�tre � la fonction du 
// Thread. Ce thread est arr�t� par le Thread principal 
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
		// Cette fonction place le thread en attente de l'�v�nement.
		// Noter que ceci n'occupe plus de temps CPU. Le thread est
		// endormi jusqu'� ce que le syst�me le r�veille lorsque 
		// l'�v�nement "hEvent" est signal�.
		//
		if( WaitForSingleObject( hEvent, INFINITE ) == WAIT_OBJECT_0 )
		{
			// Boucle tant que des �v�nement sont d�pil� de la FIFO
			while( Ic_GetEvent( hCanal, &event ) == _OK )
			{	
				count++;
				// Affiche une ligne de texte d�crivant l'�v�nement
				GetEventString( &event, string );				
				Echo( " Evt% 4d %s", count, string );
			}
		}
	}	
	return 0;
}

//-----------------------------------------------------
// Fonctions diverses utilis�e par le programme de test
// Versatile functions used by the test program
//-----------------------------------------------------

// Echo
// ----
// Cette fonction correspond � "printf" mais avec une protection
// contre les acc�s simultan�s a l'affichage. En effet, le Thread et
// le programme principal peuvent acceder simultan�ment � l'�cran 
// ce qui peut provoquer affichages erron�s.
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

	// Synchronise les acc�s a l'�cran par diff�rent Threads
	WaitForSingleObject( hMutex, INFINITE );
	puts( buffer );
	ReleaseMutex( hMutex );
}

// GetCodeString
// -------------
// Retourne le nom explicite du code erreur pass� en param�tre
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
// Retourne le nom explicite du type de la carte pass� en param�tre
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
// Cette fonction retourne une ligne de texte format� d�crivant les 
// param�tres principaux de l'event point� par "pEvent". "string" doit 
// pointer sur un buffer suffisamment grand pour contenir le texte.
//
void GetEventString( t_CANevent* pEvent, char* string )
{
	int i;
	char tmp[80];

	memset( tmp,0x00,sizeof(tmp));
	*string = (char)NULL;

	// Affiche le type de l'�v�nement
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

	// Affiche les octets de donn�e
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


