
// Fichier de définition du programme d'exemple
// CANTEST.C

// Header file for CANTEST.C sample program

// Prototypes des fonctions
// Function prototypes
//
DWORD Thread( HANDLE hEvent );
char* GetCodeString( short value );
char* GetStatusString( t_StatusRq status );
char* GetBoardTypeString( unsigned long boardType  );
char* GetFrameType( t_CANframeType frameType );
char* GetDiagOnCANstate( int state );
char* GetChipState( int state );



void GetEventString( t_CANevent* pEvent, char* string );
 int __cdecl _output ( FILE* , const TCHAR *format, va_list argptr );
void __cdecl Echo( const char*, ... );

// Valeur de l'identificateur a émettre
// Idenfier's value to transmit
//
#define CAN_IDENT		0x200
#define CAN_FC_IDENT	0x100