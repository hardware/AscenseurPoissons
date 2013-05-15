/*
-----------------------------------------------------------
 CANDEFEX.H  Copyright (c) 2006 NSI (Annecy France)
-----------------------------------------------------------
Author :   CRO
Product :  CANPC2000EX Interface
File    :  Data structures and values declarations
Target  :  Windows 32 DLL 
-----------------------------------------------------------

Ce fichier contient les definitions :
  - Des structures de données utilisées par les fonctions de
  - l'interface CAN.
  - Des valeurs constantes utilisées comme paramètres.
  - Des codes de retour des fonction de l'interface CAN.

  MISE EN GARDE IMPORTANTE : Il faut s'assurer que le compilateur
  utilisé peut appliquer la directive d'alignement des champs 
  des structures de données suivante:

    #pragma pack(push,2)

  Ceci peut changer la taille des structures et la position
  des champs. Si cette directive n'est pas appliquée, LES 
  FONCTIONS DE L'INTERFACE LOGICIELLE NE FONCTIONNERONT PAS 
  CORRECTEMENT.
*/


/*
   Cette directive indique que les champs des structures de
   données doivent tous commencer à des addresses paires.
   NE PAS SUPPRIMER. Cette syntaxe est specifique aux 
   compilateurs Microsoft. Faire les changements nécessaires 
   pour d'autres compilateurs.
*/

#pragma pack(push,2)

#ifndef _NSI_COMMON_CODE

    /* Codes retour des fonctions */
	#define _OK					0x0050
	#define _MEM_ERR			0x0051
	#define _SEQ_ERR			0x0052
	#define _PARAM_ERR			0x0053
	#define _CHIP_ERR			0x0054
	#define _ID_OVERFLOW		0x0057
	#define _UNKNOWN_ID			0x0058
	#define _EMPTY_BUF			0x0059
	#define _EMPTY_FIFO			0x005A
	#define _FRAME_TYPE_ERR		0x005B
	#define _INTERFACE_ERR		0x005C
	#define _BUF_OCCUPIED		0x005D  
	#define _TMO_ERR			0x005E
	#define	_SLEEP_MODE			0x0060
	#define _BOARD_ERR			0x0061
	#define _UNKNOWN_PERIOD		0x0062
	#define _PERIODIC_OVERFLOW	0x0063
	#define _INVALID_OP			0x0081
	#define _DRV_PARAM_ERR		0x00F0

	#define _USB_ERR			0x00F1
	#define _BOARD_TIMEOUT		0x00F2
	#define _RS232_ERR			0x00F5

	#define	_OPENING_DRV_ERR	0x00FF

    // Mode de l'interface
	typedef enum
	{                 
		_BUFFER		= 1,		/* Buffer	*/
		_FIFO		= 2,		/* Fifo		*/
		_ANALYSE	= 3			/* Analyse  */
	} t_Interface;

    // Informations de configuration d'une carte
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
	} t_CardData;

    // Demande de compte rendu des événements reseau
	typedef enum
	{
		_NO_STATUS = 0,
		_STATUS = 1
	} t_StatusRq;


	#define _NSI_COMMON_CODE
#endif

// Code retour supplementaire (CAN seulement)
#define _DOWNLOAD_BUF_OCCUPIED		0x64 // Warning: value of v1.06 is 0x70

// Mode d'interface supplémentaire
#define _ANALYSE_DC_PSA		0x10 // Diag on CAN spy (PSA)

// Liste des types de périphériqes CAN
#define _CANPCISA		1	// CANPC, CANPCa, CANPCMCIA, CAN104
#define _CANPCI2P		2	// CANPCI
#define _CANPCUSB		3   // CAN-USB Interface
#define _OBDUSB			4   // MUXy, MUXy light
#define _USBBOX			5	// MUXyBox
#define _USBBECOMM		6
#define _USBMUXY2		7	// MUXy2010 et MUXybox 2

// Liste des cartes CAN
#define _CANPC				0x50
#define	_CANPC_OPTO			0x51
#define	_CANPCA				0x60
#define	_CANPCA_LS			0x61
#define	_CANPCA_OPTO		0x62
#define	_CANPCMCIA			0x80
#define	_CANPCMCIA_LS		0x81
#define	_CANPCMCIA_OPTO		0x82
#define	_CANPCI				0x70
#define	_CANPCI_LS			0x71
#define	_CANPCI_OPTO		0x72
#define	_CANUSB				0x73
#define _CAN_OBDUSB			0x74	// MUXy
#define _CANEX_OBDUSB		0x75	// MUXy (ISO-15765)
#define _MUXYBOX			0x76	// MUXy box
#define _MUXYBOX_KWPTEST	0x77	// MUXy box (KWP_Test)
#define _BECOMM				0x78
#define _MUXYLIGHT			0x79	// MUXy light
#define _MUXY2				0x7A	// Modif YMO 20.04.10

// Liste des controleur CAN
#define _CAN_82527		0x90	// Intel i82527
#define _CAN_SJA1000	0x91	// Philips SJA1000
#define _CAN_90F543		0x92	// Fujitsu 90F543
#define _CAN_NECV850	0x93	// Micro NEC V850  - Ajout YMO 20.04.10

// Type de CAN
#define _CAN_HIGH_SPEED	0x00
#define _CAN_LOW_SPEED	0x01

// Nombre de repetition periode
#define _CAN_INFINITE   -1

// Taille maximale des données CAN
#define _CAN_MAX_DATA			8		// CAN data
#define _CAN_MAX_DATA_EX		4095	// CAN segmented data
#define _CAN_MAX_PATTERN		256		// CAN pattern data (periodical)

// Valeur d'identificateur invalide pour usage spécial
#define _CAN_DUMMY_ID				0x7FFFFFFF
#define _CAN_ALL_ID					0x7FFFFF0A
#define _CAN_EVENT_BOFF				0x8FFFFFFF
#define _CAN_EVENT_WARNING_LEVEL	0x8FFFFF00
#define _CAN_EVENT_PASSIVE_ERROR	0x8FFFFF01
#define _CAN_EVENT_WAKE_UP			0x8FFFFF02
#define _CAN_EVENT_KWPTEST			0x8FFFFF03
#define _CAN_EVENT_CUSTOM			0x8FFFFF04

// Type d'identificateur
typedef enum
{            
	_CAN_STD = 0,			/* Standard 11 bits */
	_CAN_EXT = 1,			/* Extended 29 bits */
	_CAN_ALL = 2
} t_CANidentType;

// Mode d'adressage pour Diag On CAN
typedef enum
{            
	_DC_NORMAL			= 0,	
	_DC_NORMAL_FIXED	= 1,
	_DC_EXTENDED		= 2
} t_CANaddressing;

// Diag On CAN frame stuffing
typedef enum
{            
    _DC_NO_PADDING	= 0,	// Variable length
    _DC_PADDING		= 1		// Fixed length (8 bytes)
} t_CANpadding;

// Type de message ou d'événement
typedef enum
{
	_CAN_TX_DATA		= 0,
	_CAN_RX_DATA		= 1,
	_CAN_TX_RX_REMOTE	= 2,
	_CAN_TX_REMOTE		= 3,
	_CAN_RX_DATA_REMOTE = 4,
	_CAN_TX_AUTO_REMOTE = 5,
	_CAN_RX_REMOTE		= 6,
	_CAN_LOST_MSG		= 7,
	_CAN_TX_SEG_DATA	= 8,
	_CAN_RX_SEG_DATA	= 9,
	_CAN_RX_FF_DATA		= 10,
	_CAN_TX_FC_DATA		= 11,
	_CAN_RX_FC_DATA		= 12
} t_CANframeType;


// Etat d'erreur du controleur CAN
typedef enum{
     _CAN_ACTIVE_ERR	= 0, // Mode normal
	 _CAN_PASSIVE_ERR	= 1,
	 _CAN_BUS_OFF		= 2,
     _CAN_UNKNOWN		= 3  // Pas disponible
} t_CANerr;

// Etat du controleur CAN
typedef enum {
     _CAN_SLEEP			= 0,	// Pas disponible
     _CAN_POWER_DOWN	= 1,	// Pas disponible
     _CAN_RESET			= 2,	// Pas disponible
	 _CAN_WAKE_UP		= 3
} t_CANstat;

// Etat du driver de ligne CAN
#define _CAN_NORMAL			0x00	// Etat
#define _CAN_LD_SLEEP		0x01	// Etat ou Cmd
#define	_CAN_NETWORK_WAKEUP	0x02	// Etat ou Cmd
#define _CAN_ERROR			0x03	// Etat

// Etat du bus CAN
typedef enum {
     _CAN_NOMINAL		= 0,	// Normal mode
     _CAN_DEGRADED		= 1,	// Communication on 1 line
     _CAN_MAJOR_ERROR	= 2,	// Major error
     _CAN_DIAG_UNKNOWN	= 3		// Unknown state
} t_CANdiag;

// Evenements DiagOnCAN
typedef enum {
	 _DC_OK						= 	0x50,
	 _DC_TIMEOUT_Ar				=	0x81,
	 _DC_TIMEOUT_As				=	0x82,
	 _DC_TIMEOUT_Bs				=	0x83,
	 _DC_TIMEOUT_N_Cr			=	0x84,
	 _DC_WRONG_SN				=	0x85,
	 _DC_UNEXP_PDU				=	0x86,
	 _DC_WFT_OVRN				=	0x87,
	 _DC_FIFO_OVRN				=	0x88,
	 _DC_DATA_LAYER_ERROR 		=	0x89,
	 _DC_USER_RESET				=	0x8A,
	 _DC_BUFF_OVRN				=	0x8B,
	 _DC_UNEXPECTED_ERROR 		=	0xF0,
     _DC_REP_NEG_TELECHARGEMENT	=	0xF1
} t_DCstate;

// Structure de déclaration d'un message CAN
typedef struct
{
    // Valeur de l'identificateur
	unsigned long	ident;			
	
    // Type de l'identificateur
    t_CANidentType	identType;

    // Type de message CAN
	t_CANframeType	frameType;

    // Demande de compte rendu
    t_StatusRq		statusRq;

    // Identificateur de controle de flux (trames segmentee seulement)
	unsigned long	identFlowControl;

    // Demande de compte rendu  pour l'identificateur de controle de flux (trames segmentee seulement)
    t_StatusRq		flowControlStatusRq;

    // Adresse source et adresse destination pour adressage étendu en Diag on CAN seulement
	unsigned char   sourceAddress;
	unsigned char   targetAddress;
		
    // RFU Reserved
	unsigned short	reserved;

    // Nombre d'octets de données
	unsigned short	dlc;
	
    // Tableau de données
	unsigned char	data[_CAN_MAX_DATA_EX];

} t_CANobj;

// Evenement CAN
typedef struct
{
    // Type de l'evenement
	t_CANframeType	eventType;

    // Etat du controleur CAN
	t_CANerr		CANerr;

    // Etat communication DiagOnCAN
	t_DCstate		DCerr;

    // Valeur de l'identificateur
	unsigned long	ident;

	/* Identifier's type
	   Type de l'identificateur */
    t_CANidentType		identType;

	/* Data bytes count
	   Nombre d'octets de données */
	unsigned short	dlc;

	/* Data bytes array
	   Tableau d'octets de données */
	unsigned char	data[_CAN_MAX_DATA_EX];

	/* Date
	   Datation */
	unsigned long	timeStamp;
	
	/* RFU
	   Reserve */
	unsigned long	reserved;
	
} t_CANevent;

/* Flow control parameters
   Parametres de controle de flux */
typedef struct
{
	unsigned short	blockSize;	// Block size
	unsigned short	STmin;		// ST min
	unsigned long	As;			// As
	unsigned long	Ar;			// Ar
	unsigned long	Bs;			// Bs
	unsigned long	Cr;			// Cr
	unsigned long	Br;			// Br 

} t_CANflowParams;

/* CAN bus parameters
   Parametres du bus CAN */
typedef struct
{
	unsigned char	baudpresc;	// Baud Rate Prescaler
	unsigned char	tseg1;		// TSEG1
	unsigned char	tseg2;		// TSEG2
	unsigned char	sjw;		// Synchronization Jump Width
	unsigned char	sample;		// Sampling mode

} t_CANbusParams;

/* CAN counters
   Compteurs CAN */
typedef struct
{
	unsigned long tx_ok;		/* transmission OK */
	unsigned long rx_ok;		/* reception OK */
	unsigned long bus_off;		/* erreur de bus off */
	unsigned long passive;		/* erreur passive */
	unsigned long stuff_err;	/* erreur de codage */
	unsigned long form_err;		/* erreur de format */
	unsigned long ack_err;		/* erreur d'acquittement */
	unsigned long bit1_err;		/* erreur bit1 */
	unsigned long bit0_err;		/* erreur bit0 */
	unsigned long crc_err;		/* erreur de checksum */
	unsigned long reserved1;	/* Reserve */
	unsigned long reserved2;	/* Reserve */
} t_CANcounter;


typedef	struct 
{
	unsigned short	bit_error;		// erreur sur un bit		
	unsigned short	form_err;		// erreur de forme sur la trame
	unsigned short	stuff_err;		// erreur de stuffing
	unsigned short	other_err;		// autre erreur
	unsigned short	id28_21;
	unsigned short	start_fr;
	unsigned short	bit_SRTR;
	unsigned short	bit_IDE;
	unsigned short	id20_18;
	unsigned short	id17_13;
	unsigned short	CRC_Seq;
	unsigned short	reserved0;
	unsigned short	data_field;
	unsigned short	data_length;
	unsigned short	bit_RTR;
	unsigned short	reserved1;
	unsigned short	id4_0;
	unsigned short	id12_5;			 
	unsigned short	empty_0;		// reservé
	unsigned short	empty_1;		// reservé
	unsigned short	act_err;
	unsigned short	interm;	
	unsigned short	tolerate_dom;	
	unsigned short	pas_err;
	unsigned short	err_del;
	unsigned short	CRC_del;
	unsigned short	ack_slot;
	unsigned short	eof;
	unsigned short	ack_del;	
	unsigned short	overload_flag;
	unsigned short	lost_Rx;		// messages perdus
	unsigned short 	frame_ok;		// transmission ou réception OK
	unsigned short 	bus_off;		// erreur de bus off
	unsigned short 	passive;		// erreur passive
}t_CANsjaCounters;

/* Controller specific data
   Informations sur le controleur CAN */
typedef struct{
	unsigned long chipType;			// Type de controleur
	union {
		struct
		{
			t_CANsjaCounters rxCounters;
			t_CANsjaCounters txCounters;
		} SJA1000;
		char	reserved[512];
	};
} t_CANchipInfo;

/* Device specific data
   Informations sur le périphérique CAN */
typedef struct{
	unsigned long deviceType;			// Type de périphérique
	union {
		struct {
			short			vendorID;				//VendorID 
			short			deviceID;				//DeviceID 
			char			productName[40];		//Nom produit
			char			manufacturerName[40];	//Fabricant
			char			serialNumber[80];		//N° de série
			short			firmwareVersion;		//Version
			unsigned long	boardType;				//Type de carte
			unsigned long	reserved;				//Réservé
			unsigned long	hardwareVersion; 		//Version harware
		}CAN_USB;
		struct {
			unsigned long	IOBaseAddress[4];		//Adresse IO 
			unsigned long	memoryBaseAddress[3];	//Mémoire de base
			unsigned long	IRQLineNumber;  		//N° IRQ
			unsigned long	boardType;				//Type de carte
  			char			cardName[80];			//Nom de carte
  			unsigned long	reserved1;				//Réservé
			unsigned long	reserved2;				//Réservé
		}CAN_PCI;
		struct {
			unsigned long	IOBaseAddress[4];		//Adresse IO 
			unsigned long	IRQLineNumber;  		//N° IRQ
			unsigned long	boardType;				//Type de carte
  			char			cardName[80];			//Nom du canal
			unsigned long	reserved1;				//Réservé
			unsigned long	reserved2;				//Réservé
		}CAN_ISA;
		char	reserved[512];
	};
} t_CANdeviceInfo;



/* Restore previous alignment specification
   Restore l'alignement des stuctures */
#pragma pack(pop)
