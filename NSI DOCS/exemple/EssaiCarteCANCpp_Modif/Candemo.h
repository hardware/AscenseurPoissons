
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
void GetEventString( t_CANevent* pEvent, char* string );
 int __cdecl _output ( FILE* , const TCHAR *format, va_list argptr );
void __cdecl Echo( const char*, ... );

// Valeur de l'identificateur à émettre
// Idenfier's value to transmit
//
#define CAN_IDENT		0x06017241