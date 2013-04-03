//    ---------------------------------
//    Programme d'exemple d'utilisation 
//    de l'interface logicielle CAN NSI
//    ---------------------------------
//
//            M O D E   F I F O
//
// Ce programme est donné à titre d'exemple. Les conséquences de 
// toute erreur ou mauvais fonctionnement de ce programme ne 
// sauraient mettre en cause la responsabilité de la société NSI. 

// Ce programme montre comment émettre et recevoir des
// trames en mode FIFO. L'émission des trames est déclenchée
// par l'appui sur des touches du clavier. La réception est
// réalisée par un Thread qui attend le remplissage de la FIFO
// pour afficher les évènements CAN.
//
//
//    ---------------------------------
//    Sample program for using the NSI
//    CAN software interface.
//    ---------------------------------
//
// This sample program is given "as is". The consequences of any 
// error or malfunction of this program will not involve NSI's 
// responsability. 
//
// This program shows how to send and received
// CAN messages in FIFO interface mode. The transmission is
// triggered by pressing on the keyboard. Receptions are performed
// by the Thread which is waiting for the CAN event to be stored
// in the FIFO to extract and display those events.
//
//------------------------------------------------------------
// NSI(c) 2003
// Copie partielle ou complète avec autorisation de NSI.
// Partial or complete copy with NSI's authorization.
//------------------------------------------------------------

#include <windows.h>
#include <conio.h>
#include <stdio.h>

// Inclusion des fichiers de déclaration des structures 
// et des fonctions de l'interface CAN.
//
// Include files of the CAN interface data structures 
// and functions prototypes declarations.
//
#include "canpcex.h"

// Prototypes des fonctions du programme d'exemple
// Sample program functions prototypes
//
#include "candemo.h"

// Variables globales
// Global variables
// ------------------
//
// Synchronisation de l'affichage
// Display synchronization
HANDLE hMutex;		
		
// Handle du canal ouvert
// Open channel handle
HANDLE hCanal = INVALID_HANDLE_VALUE;

// Handle de l'évènement FIFO
// FIFO event handle
HANDLE hEvent = INVALID_HANDLE_VALUE;

//  MAIN( )
//-----------
// Fonction principale du programme d'exemple.
// Main function of the sample program.
//
void main( void ) 
{	
	// Variables internes diverses
	// Various internal variables
	int				i;
	short			cr;
	BOOL			done = FALSE;
	short			canal;
	char			key[2];
	short			DLL,DRV;
	unsigned long	cardCount;	
	unsigned char	data[_CAN_MAX_DATA_EX];

	// Variables de controle du Thread
	// Thread control variables
	DWORD threadId;
	HANDLE hThread;
	
	// Structure d'initialisation d'un message CAN
	// Initialization structure for a CAN message
	t_CANobj canObj;
	
	// Structures d'initialisation du bus CAN
	// Initialization structures for CAN bus
	t_CANbusParams canBus;
	
	// Tableau pour recevoir la configuration des canaux
	// Structure array to receive channel configuration data
	t_CardData cardData[10];

	// Crée les ressources systèmes nécessaires au programme
	// pour fonctionner en mode FIFO.
	//
	// Create system resources needed for test program to 
	// run in FIFO mode.
	// ----------------------------------------------------
	//
	// En mode FIFO, un évènement peut être est signalé à chaque
	// fois que la FIFO n'est plus vide. Ceci permet de réveiller 
	// une partie du programme placée en attente de cet évènement.
	// Ce programme en attente est un "Thread" dont la fonction 
	// est de dépiler les évènements de la FIFO puis de se 
	// rendomir lorsque la FIFO est de nouveau vide. Cet event doit
	// être crée par l'application puis fourni à l'interface.
	//
	// In FIFO mode, when data is placed into the FIFO while the
	// FIFO empty, an event can be signaled. This can wake-up a
	// program which was waiting for this event. This program is
	// a Thread which job is to extract event from the FIFO until
	// the FIFO is empty and then go back to sleep. This event 
	// object must be created by the application and then given to
	// the interface.
	//
	hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

	// Crée l'objet "mutex" qui permet d'éviter les conflicts 
	// entre le thread principal (main) et le thread de d'extraction
	// de la FIFO (Thread)
	//
	// Create mutex object to avoid display conflict between main
	// thread and the FIFO extractor thread (Thread)
	//
	hMutex = CreateMutex( NULL, FALSE, NULL );

	// En mode FIFO, les réceptions et les émission de messages CAN 
	// sont placées dans la FIFO. Une partie du programme (le Thread) 
	// attend que la FIFO ne soit plus vide pour en extraire les 
	// informations. La fonction CreateThread crée et démarre ce 
	// THREAD. Voir la fonction Thread( ).
	//
	// In FIFO mode, receptions and transmission of CAN messages are
	// stored into the FIFO list. A program (the Thread) is waiting for
	// the FIFO not to be empty to extract the data. The CreateThread
	// function is creating and starting this THREAD. See the Thread( ) 
	// function.
	//
	hThread = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)Thread,
		hEvent,
		0,
		&threadId );
	
	// Ic_EnumCards
	// ------------
	// Lorsque plusieurs canaux CAN sont disponibles dans un même
	// PC, il est utile de connaitre les particularités de chaque
	// canal pour choisir lequel utiliser. Cette fonction retourne 
	// la liste des canaux utilisables dans un tableau. L'indice 
	// du tableau correspond au numéro du canal.
	//
	// When more than one CAN channel is available in the same PC,
	// it is usefull to know each channel properties to choose the 
	// one to use. This function returns the list of the available 
	// channels in a array. The index corresponds to the channel's
	// number.
	//
	cr = Ic_EnumCards( &cardCount, cardData, sizeof( cardData ));

	Echo( "Ic_EnumCards : %s.", GetCodeString( cr ) );
	if( cr != _OK )
	{
		Echo(" Failed to get CAN channels list." );
		getch( );
		return;
	}

	// Affiche la liste des canaux (cartes) et trouve le premier 
	// canal disponible. L'index de ce canal est placé dans la 
	// variable "canal". Sinon -1 ce qui indique aucun canal libre.
	//
	// Display the channel list and find the first available.
	// The index of this channel is placed into the "canal" variable.
	// Otherwise the value is -1 which mean no available channel.
	//
	Echo( "  Detected Boards : %d", cardCount );
	canal = -1;
	for( i=0; i<(int)cardCount; i++ )
	{
		Echo("  %d - IO:% 4Xh Mem:% 8Xh IRQ:% 2d  %s (%d)", 
			i,
			cardData[i].IOBaseAddress,
			cardData[i].memoryBaseAddress,
			cardData[i].IRQLineNumber,
			cardData[i].cardNameString,
			cardData[i].cardAlreadyOpen );

		// Trouve le premier canal disponible cad non utilisé au même
		// moment par une autre application.
		//
		// Finds the first available channel, ie not used by any other
		// programs at the same time.
		if( canal == -1 && cardData[i].cardAlreadyOpen == FALSE ) 
		{
			canal = i;
		}
	}

	// Vérifie qu'au moins un canal est disponible
	// Check that at least one channel is available
	if( canal < 0 )
	{
		Echo("  CAN DEMO needs at least one available CAN channel..." );
		getch( );
		return;
	}

	// Ic_InitDrv
	// ----------
	// Selectionne et initialise un canal CAN. La valeur du premier paramètre
	// indique l'indice du canal que l'on veut utiliser. Celui-ci correspond
	// à l'indice dans le tableau retourné par Ic_EnumCards. Un "Handle" est
	// retourné dans la variable "hCanal". Cette valeur permet d'identifier ce
	// canal et éventuellement d'utiliser plusieurs canaux. Cette valeur est 
	// passée à toutes les autres fonctions de l'interface logicielle CAN.
	//
	// Select and initisalize a channel. The value of the first parameter
	// indicates the channels index to be used. This value is the same index 
	// used in the tab returned by Ic_EnumCards. The returned "hCanal" value
	// identifies this channel and allows to eventually use more than one
	// channel simulteanously. It is passed to all the other function calls 
	// to the CAN software interface.
	//
	cr = Ic_InitDrv( (short)canal, &hCanal );

	Echo("Ic_InitDrv( %d,%Xh ) : %s.", canal, hCanal, GetCodeString( cr ));
	if( cr != _OK )
	{
		Echo(" Unable to select CAN channel #%d.", canal );
		getch( );
		return;
	}

// Ic_GetAPIinfo
	// ---------------
	// Retourne le type de la carte du canal initialisé et les version des 
	// fichiers de l'interface logicielle.
	//
	// Returns the board type of the channel and the versions of the software
	// interface files.
	//
	cr = Ic_GetAPIinfo( hCanal, &DLL, &DRV, NULL );
	Echo("Ic_GetAPIinfo : %s (Dll:%.2f,Drv:%.2f)", 
		GetCodeString(cr),
		DLL / 100.0, 
		DRV / 100.0 );
	if( cr != _OK ) done = TRUE;

	// Ic_InitChip
	// -----------
	// Initialise le controleur CAN: Le débit (250kbit, echant. 75%)	
	// Initialize the CAN controler : BitRate (250kbit, sample at 75%)
	//
	canBus.baudpresc	= 2;	// BRP	 = 2
	canBus.tseg1		= 11;	// TSEG1 = 11
	canBus.tseg2		= 4;	// TSEG2 = 4
	canBus.sjw			= 1;	// SJW	 = 1
	canBus.sample		= 0;	// SPL	 = 0 (1 sample)

	// Les 2 derniers parametres sont reserves a une utilisation DiagOnCAN avec MUXy
	//	- _DC_NORMAL	: Mode d'adressage Normal
	//	- _DC_NO_PADDING: Les trames CAN ont une longueur variable selon la longueur du message 
	// The last 2 parameters are for DiagOnCAN only and are significant for MUXy only
	//	- _DC_NORMAL	: Normal addressing
	//	- _DC_NO_PADDING: No fixed length for CAN frame. 
	//
	cr = Ic_InitChip( hCanal, canBus, _DC_NORMAL, _DC_NO_PADDING );
	
	Echo("Ic_InitChip( 250kbit,75%,1SJW,1SPL ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_InitInterface
	// ----------------
	// Initialise l'interface CAN: Le mode de gestion des évènements 
	// (FIFO ou Buffer) et évèntuellement la taille de la FIFO
	//
	// Initialize the CAN interface: The event passing mode (FIFO or 
	// buffer) and eventually the desired size for the FIFO
	//
	cr = Ic_InitInterface( hCanal, _FIFO );

	Echo("Ic_InitInterface( FIFO ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_ConfigEvent
	// -----------
	// Indique à l'interface logicielle le HANDLE de l'évent devant être 
	// utilisé pour signaler les évènements concernant la FIFO. Voir les
	// fonction Thread et CreateEvent.
	//
	// Indicates to the CAN interface the HANDLE of the event object used 
	// to signal events about the FIFO. See the Thread and CreateEvent
	// functions.
	//
	cr = Ic_ConfigEvent( hCanal, hEvent, 0 );

	Echo( "Ic_ConfigEvent( ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Déclaration d'une trame de données en émission segmentee portant 
	// l'ident CAN_IDENT avec demande d'acquittement. Dans un premier 
	// temps, on initialise la structure 'canObj' contenant les informations 
	// du message CAN.
	//
	// Declaration of a segmented data transmition frame with identifier 
	// CAN_IDENT and acknowledge request. First step: initialize the 'canObj' 
	// structure  that is to contains the CAN message configuration data.
	// ------------------------------------------------------------------
	//
	// Valeur de l'identificateur du message 0x000-0x7FF pour un ident STD.
	// Message identifier's value 0x000-0x7FF for Standard ident.
	canObj.ident	= CAN_IDENT;

	// Demande de compte rendu pour ce message. En mode FIFO, ce 
	// paramètre est indispensable pour que le compte rendu de
	// l'échange soit placé dans la FIFO.
	//
	// Status report request for this message. In FIFO mode, this
	// parameter is required so that exchange status report can
	// be found in the FIFO.
	canObj.statusRq	= _STATUS;

	// Type de l'identificateur
	// Identifier's type
	canObj.identType = _CAN_STD;

	// Valeur de l'identificateur de controle de flux pour l'identificateur CAN_IDENT.
	// Flow control identifier for CAN_IDENT ident.
	canObj.identFlowControl		= CAN_FC_IDENT;

	// Demande de compte rendu pour le message de controle de flux. 
	//
	// Status report request for the flow control message. 
	canObj.flowControlStatusRq	= _STATUS;

	// Type du message CAN
	// CAN message type
	canObj.frameType = _CAN_TX_SEG_DATA;

	// Taille de la zone de données du message en octets 0-4095
	// Data size in message in bytes 0-4095
	canObj.dlc		 = 4095;	

	// Valeurs des octets de données
	// Data bytes values
	for( i = 0; i < canObj.dlc; i++ )
	{
		canObj.data[0] = i;
	}
	
	// Ic_InitId
	// ---------
	// Déclare le message CAN dont les données sont dans passées 
	// la structure pointée par le second paramètre (canObj).
	//
	// Declare the CAN message which data are given in the structure
	// pointed by second parameter (canObj).
	//
	cr = Ic_InitId( hCanal, &canObj );
	
	Echo( "Ic_InitId( %03Xh,%d,TX_SEG_DATA ) : %s.", canObj.ident, canObj.dlc, GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_SetRxMask
	// ------------
	// Déclare la réception des trames de données d'un groupe 
	// d'identificateur définis par un masque de bits. Dans cet
	// exemple, on recoit tous les identificateurs (STD et EXT).
	//
	// Declare the reception of data frames with a specified
	// group of identifiers values. Theses values are defined
	// with a "bit mask". In this exemple we want to receive
	// all identifiers values (STD and EXT).

	cr = Ic_SetRxMask( hCanal, 0x000, 0x000, _CAN_ALL );

	Echo( "Ic_SetRxMask( ALL ) : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Ic_StartChip
	// ------------
	// Démarre le controleur CAN. Les réceptions, démarrent à cet instant.
	// Le controleur acquitte les trames correctement formatées qui 
	// circulent sur le réseau.
	//
	// Start CAN controler. Receptions are starting now. The controler
	// is seting the acknowledge bit for all correctly formated frame
	// on the CAN bus.
	//
	cr = Ic_StartChip( hCanal );
	Echo( "Ic_StartChip : %s.", GetCodeString(cr));
	if( cr != _OK ) done = TRUE;

	// Teste que l'initialisation et le démarrage du canal CAN on été
	// réussies. En cas d'échec, le programme est arrêté.
	//
	// Check that CAN channel initialization and starting have been
	// succesfull. In case of a failure, the program is stopped.
	//
	if( done )
	{
		Echo( " Failed to initialize CAN interface. Program will stop." );
	}
	else
	{
		Echo( " " );
		Echo( " Press [A] key to transmit ID %03Xh ", CAN_IDENT );
		Echo( " Press [ESC] to exit program " );
	}

	key[1] = 0;

	memset( data, 0x00, sizeof(data) );
	
	// Boucle tant que la touche ESC n'est pas pressée.
	// Loop while ESC key is not pressed.
	//	
	while( !done )
	{
		key[0] = getch( );
		strupr( key );
		switch( key[0] )
		{
		case 'A' :

			// Prépare les données à transmettre dans le message
			// Prepare data to transmit in message
			//
			for( i=0; i<32; i++ ) data[i] = i;

			// Ic_TxMsg
			// --------
			// Met a jour les données et active la transmission du message 
			// portant l'identificateur passés en paramètre.
			//
			// Update data and activate the transmission of a frame with 
			// the given identifier.
			//			
			cr = Ic_TxMsg( hCanal, CAN_IDENT, 32, data );
	
			Echo( "Ic_TxMsg( %03Xh,32,DATA ) : %s", CAN_IDENT, GetCodeString( cr ));
			break;

		case (char)27 :
			// Indique que la boucle while doit se terminer
			// Indicates that while loop has to end
			done = TRUE;
			break;

		default :			
			Echo( "[A]ctiveID - [ESC] Exit" );
		}
	}

	// Ic_ExitDrv
	// ----------
	// Ferme le handle du canal et libère le canal pour que d'autres
	// applications puissent l'utiliser
	//
	// Close the HANDLE for this channel and free it so that other
	// programs can now use it.
	//
	cr = Ic_ExitDrv( hCanal );
	
	Echo( "Ic_ExitDrv : %s", GetCodeString(cr));

	// Arrête l'éxecution du Thread.
	// Terminate the thread execution.
	TerminateThread( hThread, 0 );

	// Libere les ressources système
	// Free system resources
	if( hEvent ) CloseHandle( hEvent );
	if( hMutex ) CloseHandle( hMutex );

	puts(" Done : Press Key...");
 	getch( );

	// Fin du programme principal
	// End of the main program
}


// Thread
// ------
// Le programme Thread est créé par le programme principal. 
// Il s'éxécute en parallèle et de manière assynchrone. Cette 
// fonction est exécutée  par le Thread. Elle attend que la 
// FIFO passe de l'état VIDE à NON VIDE. Ceci est signalé par 
// un "event". Le thread attend  que l'event soit signalé pour 
// dépiler le ou les évènements présents dans la FIFO. Le 
// HANDLE de l'event est passé en paramètre à la fonction du 
// Thread. Ce thread est arrêté par le Thread principal 
// lorsqu'il se termine.
//
// The thread is created by the main program. It is running in
// parallel with it and is totally assynchronous. This function 
// is executed by the Thread. It is is waiting for the FIFO to
// become NOT EMPTY which is signaled with an EVENT. The thread
// is waiting for the event to be signaled to extract one or more
// event from the FIFO. The event's hCanal is passed as a parameter
// to the thread's function. This thread si stopped when the main
// thread terminates.
//
DWORD Thread( HANDLE hEvent )
{
	t_CANevent event;
	long count = 0;
	char string[0x100];

	// Boucle "infinie" (tant que le thread principal fonctionne)
	// "Infinite" loop (until the program stops running)
	while( 1 )
	{
		// Cette fonction place le thread en attente de l'évènement.
		// Noter que ceci n'occupe plus de temps CPU. Le thread est
		// endormi jusqu'à ce que le système le réveille lorsque 
		// l'évènement "hEvent" est signalé.
		//
		// This function call puts the thread to sleep and waiting 
		// for the event. Note that this is not using any CPU time. 
		// The thread is asleep until the OS wake it up when the 
		// event is signaled.
		//
		if( WaitForSingleObject( hEvent, INFINITE ) == WAIT_OBJECT_0 )
		{
			// Boucle tant que des évènement sont dépilé de la FIFO
			// Loop while events are found in FIFO
			while( Ic_GetEvent( hCanal, &event ) == _OK )
			{	
				count++;
				// Affiche une ligne de texte décrivant l'évènement
				// Display a line of text discribing the event.
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
// This function is working like "printf" but with a protection
// against simultaneous acces to the diplay window. Thus, the Thread
// and the main program may try to display strings at the same time 
// which will cause wrong display.
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
	// Synchronise access to screen display by more than one Thread
	WaitForSingleObject( hMutex, INFINITE );
	puts( buffer );
	ReleaseMutex( hMutex );
}

// GetCodeString
// -------------
// Retourne le nom explicite du code erreur passé en paramètre
//
// Returns the explicit name of the given error code
//
char* GetCodeString( short cr )
{
	switch( cr )
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

// GetBoardTypeString
// ------------------
// Retourne le nom explicite du type de la carte passé en paramètre
//
// Returns the explicit board type name of the given type
//
char* GetBoardTypeString( unsigned long type )
{
	switch( type )
	{
	case _CANPC : return "CANPC";
	case _CANPC_OPTO : return "CANPC/OP";
	case _CANPCA : return "CANPCa";
	case _CANPCA_LS : return "CANPCa/LS";
	case _CANPCA_OPTO : return "CANPCa/OP";
	case _CANPCMCIA : return "CANPCMCIA";
	case _CANPCMCIA_LS : return "CANPCMCIA/LS";
	case _CANPCMCIA_OPTO : return "CANPCMCIA/OP";
	case _CANPCI : return "CANPCI";
	case _CANPCI_LS : return "CANPCI/LS";
	case _CANPCI_OPTO : return "CANPCI/OP";
	case _CANUSB : return "CAN-USB";
	case _CAN_OBDUSB : return "MUXy";
	case _CANEX_OBDUSB : return "MUXy (ISO 15765-2)";
	case _MUXYBOX : return "MUXy box";
	case _MUXYBOX_KWPTEST : return "MUXy box (KWP_Test)";
	case _MUXYLIGHT	: return "MUXy light";
	default : return "BOARD ???";
	}
}

char* GetChipState( int state )
{
	switch( state )
	{
	case _CAN_ACTIVE_ERR : return "NORM";
	case _CAN_PASSIVE_ERR : return "PASV";
	case _CAN_BUS_OFF : return "BUS OFF";
	case _CAN_UNKNOWN : return "UNKN";
	default : return "????";
	}
}


char* GetDiagOnCANstate( int state )
{
	switch( state )
	{
	case _DC_OK			:			return "NO_ERROR";
	case _DC_TIMEOUT_Ar	:			return "TIMEOUT_AR";
	case _DC_TIMEOUT_As	:			return "TIMEOUT_AS";
	case _DC_TIMEOUT_Bs	:			return "TIMEOUT_BS";
	case _DC_TIMEOUT_N_Cr	:		return "TIMEOUT_CR";
	case _DC_WRONG_SN		:		return "INVALID_SN";
	case _DC_UNEXP_PDU		:		return "UNEX_PDU";
	case _DC_WFT_OVRN		:		return "WFT_OVRN";
	case _DC_FIFO_OVRN		:		return "FIFO_OVRN";
	case _DC_DATA_LAYER_ERROR	:	return "DL_ERR";
	case _DC_USER_RESET			:	return "USER_RESET";
	case _DC_UNEXPECTED_ERROR	:	return "UNEX_ERR";
	default : return "????";
	}
}



// GetFrameType
// -------------
// Retourne le nom explicite du type de message passé en paramètre
//
// Returns the explicit name of message type
//
char* GetFrameType( t_CANframeType frameType )
{
	switch( frameType )
	{
	case _CAN_TX_DATA : return "TXD";
	case _CAN_TX_SEG_DATA : return "TXS";
	case _CAN_RX_DATA : return "RXD";
	case _CAN_TX_FC_DATA : return "TXF" ;
	case _CAN_RX_FC_DATA : return "RXF" ;
	case _CAN_RX_SEG_DATA : return "RXS";
	case _CAN_RX_FF_DATA : return "RX1";
	case _CAN_TX_RX_REMOTE : return "TRR";
	case _CAN_TX_REMOTE : return "TXR"; 
	case _CAN_RX_DATA_REMOTE : return "RXR";
	case _CAN_TX_AUTO_REMOTE : return "TAR";
	case _CAN_RX_REMOTE : return "RRM";
	case _CAN_LOST_MSG : return "LST";
	default : return "??? ";				
	}
}


// GetEventString
// --------------
// Cette fonction retourne une ligne de texte formaté décrivant les 
// paramètres principaux de l'event pointé par "pEvent". "string" doit 
// pointer sur un buffer suffisamment grand pour contenir le texte.
//
// This function returns a formated char string describing the main
// data in the event structure pointed by "pEvent". "string" must point
// to a buffer large enough to contain the text.
//
void GetEventString( t_CANevent* pEvent, char* string )
{
	int i;
	char tmp[0x100];
	static DWORD time;
	
	*string = (char)0;
	
	// Affiche la datation. La résolution est 100µs. L'affichage est en millisecondes.
	// Display event time. The resolution is 100µs. The display is in milliseconds.
	sprintf( string, " %.1f ", (pEvent->timeStamp - time ) / 10.0);
	time = pEvent->timeStamp;

	sprintf( string, " %s ", GetChipState( pEvent->CANerr ));

	// Affiche le type de l'évènement
	// Display the event type
	strcat( string, GetFrameType( pEvent->eventType ));

	if( pEvent->eventType == _CAN_RX_SEG_DATA	||
		pEvent->eventType == _CAN_TX_SEG_DATA	||
		pEvent->eventType == _CAN_RX_FF_DATA	|| 
		pEvent->eventType == _CAN_RX_FC_DATA	||
		pEvent->eventType == _CAN_TX_FC_DATA	)
	{
		sprintf( tmp, " {%s} ", GetDiagOnCANstate( pEvent->DCerr ) );
		strcat( string, tmp );
	}
	
	// Affiche la valeur de l'identificateur et la taille de la trame
	// Display the event value and the frame data size
	sprintf( tmp, " %03xh [% 2d] ", pEvent->ident, pEvent->dlc );
	strcat( string, tmp );
	if( pEvent->eventType == _CAN_RX_DATA		 || 
		pEvent->eventType == _CAN_RX_DATA_REMOTE || 
		pEvent->eventType == _CAN_RX_SEG_DATA	 ||
		pEvent->eventType == _CAN_RX_FC_DATA	 )
	{
	// Affiche les octets de donnée
	// Display the data bytes
		for( i=0; i<pEvent->dlc && i<=_CAN_MAX_DATA_EX; i++ )
		{
			if(i < 0x1F)
			{
				sprintf( tmp, "%02x ", pEvent->data[i] );
				strcat( string, tmp );
			}
			else
			{
				strcat( string, "...." );
				break;
			}
			
		}
	}

}


