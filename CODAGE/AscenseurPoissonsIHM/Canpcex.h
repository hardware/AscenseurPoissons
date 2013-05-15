/*
-----------------------------------------------------------
 CANPCEX.H  Copyright (c) 2003 NSI (Annecy France)
-----------------------------------------------------------
Author :   CRO
Product :  CANEX Interface
File    :  Main include file for user applications
Target  :  Windows 32 DLL 
-----------------------------------------------------------
*/

#ifndef _CANEXINTFCDLL
/*
	Le symbole _CANAPI definit la convention d'appel des 
	fonctions de la DLL. Il est utilise dans CANPROEX.H. Il 
	faut s'assurer que la syntaxe suivante qui est 
	spécifique aux outils Microsoft est correctement 
	interpretee par le compilateur utilisé.
*/	
    #define _CANAPI __declspec(dllimport) __stdcall
#else
    #define _CANAPI __declspec(dllexport) __stdcall
#endif

/* 
   Définition des structures et des données
*/
#include "candefex.h"

/*
   Déclaration des prototypes des fonctions
*/	
#include "canproex.h"

