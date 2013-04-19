
FRANCAIS
--------
Ce programme d'exemple a �t� construit avec l'environnement
de d�veloppement Visual C++. Il utilise le fichier NSICAN.LIB 
pour la compiliation et NSICAN.DLL dans un r�pertoire du 
syst�me pour fonctionner correctement.

CANDEMO.C utilise des fonctions de l'API Win32. Pour compiler
ce programme avec un autre outil de d�veloppement que VC++,
il sera probablement n�cessaire de reg�n�rer le fichier .LIB 
et d'inclure les librairies permettant d'utiliser les
fonctions de l'API Win32 dand le nouvel environnement.

Les commentaires dans le code expliquent en d�tail le 
fonctionnement et l'utilisation des fonctions principales
de l'interface logicielle CAN.

Contenu du r�pertoire d'exemple :
CANDEMO.C      : Fichier source du programme d'exemple
CANDEMO.H      : Fichier de d�claration des prototypes
CANPC.H
CANDEF.H
CANPRO.H
NSICAN.LIB


ENGLISH
-------
This example program was build with Visual C++. It is 
using NSICAN.LIB for compiling and NSICAN.DLL for working 
properly in some system directory.

CANDEMO.C is usign some functions of the Win32 API. To 
compile this program with an other development tool than
Visual C++, it is likely that the LIB file has to be 
recreated and appropriate libraries for API Win32 have to
be included.

Comments in the code explain with details how to use the 
main function of the CAN interface.

Contents of the sample program directory :
CANDEMO.C      : Source file of the sample program
CANDEMO.H      : Header file
CANPC.H
CANDEF.H
CANPRO.H
NSICAN.LIB
CANDEMO.MDP    : Project File
