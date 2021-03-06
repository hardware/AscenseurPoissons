#ifndef ASCPDEF_H
#define ASCPDEF_H

#include <windows.h>

/**
 * @def Nombre maximum de thread exécutés par l'application
 */
#define NB_MAX_THREADS 4

/**
 * @struct THREAD_PARAMS
 * @brief Structure contenant les paramètres du thread
 */
typedef struct tagTHREAD_PARAMS
{
    ULONG  ident;   /*!< Identificateur CAN */
    HANDLE hCanal;  /*!< Identificateur du canal */
    HANDLE hEvent;  /*!< Identificateur de l'évènement */
    HANDLE hThread; /*!< Identigicateur du thread */
} THREAD_PARAMS, *LPTHREAD_PARAMS;

/**
 * @enum t_identTrame
 * @brief Identificateurs CAN
 *
 * [COFFRET PECHEUR]
 * - Identificateur en émission  RxPDO1 pour les sorties TOR         (COB-ID = 0x210) (DLC = 2 octets)
 * - Identificateur en réception TxPDO1 pour les entrées TOR         (COB-ID = 0x190)
 * - Identificateur en réception TxPDO2 pour les entrées analogiques (COB-ID = 0x290)
 *
 * [SOMMET ASCENSEUR]
 * - Identificateur en émission  RxPDO1 pour les sorties TOR         (COB-ID = 0x220) (DLC = 1 octet)
 * - Identificateur en réception TxPDO1 pour les entrées TOR         (COB-ID = 0x200)
 */
typedef enum {
     _ENTREESTOR_COFFRET_ID = 0x190,
     _ENTREESTOR_SOMMET_ID  = 0x200,
     _SORTIESTOR_COFFRET_ID = 0x210,
     _SORTIESTOR_SOMMET_ID  = 0x220,
     _CAPTEURS_COFFRET_ID   = 0x290
} t_identTrame;

typedef struct {

    union {
        struct {
            UCHAR monteeGrille:1;
            UCHAR descenteGrille:1;
            UCHAR monteeVanne:1;
            UCHAR descenteVanne:1;
            UCHAR chauffageHuile:1;
            UCHAR demarragePompe:1;
            UCHAR bNC1:2;
            UCHAR monteeCuve:1;
            UCHAR descenteCuve:1;
            UCHAR petiteVitesse:1;
            UCHAR grandeVitesse:1;
            UCHAR marcheCentraleHydralique:1;
            UCHAR bNC2:3;
        } word_16bits;

        WORD val;

    } sTor;

    union {
        struct {
            UCHAR detectHautGrille:1;
            UCHAR detectBasGrille:1;
            UCHAR detectHautVanne:1;
            UCHAR detectBasVanne:1;
            UCHAR niveauBasPoire:1;
            UCHAR defautMouDeCable:1;
            UCHAR detecteurSurcharge:1;
            UCHAR bNC1:1;

            UCHAR premiereCameSelecteurCadence:1;
            UCHAR deuxiemeCameSelecteurCadence:1;
            UCHAR troisiemeCameSelecteurCadence:1;
            UCHAR cuveDetecteurHaut:1;
            UCHAR cuveDetecteurHautGVPV:1;
            UCHAR cuveDetecteurBasGVPV:1;
            UCHAR cuveDetecteurTresBas:1;
            UCHAR bNC2:1;

            UCHAR confirmationMarchePompe:1;
            UCHAR confirmationMonteeCuve:1;
            UCHAR confirmationDescenteCuve:1;
            UCHAR confirmationPetiteVitesse:1;
            UCHAR confirmationGrandeVitesse:1;
            UCHAR confirmationCentrale:1;
            UCHAR bNC3:2;
        } dword_24bits;

        DWORD val;

    } eTor;

    union {
        struct {
            USHORT niveauEauAval:16;
            USHORT niveauEauAmont:16;
        } dword_32bits;

        DWORD val;

    } eAnalogique;

} t_coffretPecheur;

typedef struct
{
    union {
        struct {
            UCHAR voyantDefautTemperature:1;
            UCHAR voyantNiveauBasPoire:1;
            UCHAR voyantDefautCycle:1;
            UCHAR voyantDefautTreuil:1;
            UCHAR voyantDefautCentraleHydraulique:1;
            UCHAR voyantDefautPompeAttrait:1;
            UCHAR compteurCycles:1;
            UCHAR defautGeneral:1;
        } byte_8bits;

        UCHAR val;

    } sTor;

    union {
        struct {
            UCHAR BPArretUrgence:1;
            UCHAR BPMonteePV:1;
            UCHAR BPMonteeGV:1;
            UCHAR BPDescentePV:1;
            UCHAR BPDescenteGV:1;
            UCHAR BPMarcheCentraleHydraulique:1;
            UCHAR BPArretCentraleHydraulique:1;
            UCHAR bNC1:1;
            UCHAR marcheManuelle:1;
            UCHAR marcheAutomatique:1;
            UCHAR BPMonteeGrille:1;
            UCHAR BPDescenteGrille:1;
            UCHAR BPMonteeVanne:1;
            UCHAR BPDescenteVanne:1;
            UCHAR BPMarchePompe:1;
            UCHAR BPArretPompe:1;
            UCHAR BPCyclePecheur:1;
            UCHAR BPLancementCycleArmoire:1;
            UCHAR BPAcquittementDefaut:1;
            UCHAR ThermostatHuile:1;
            UCHAR NiveauBasHuile:1;
            UCHAR bNC2:3;
        } dword_24bits;

      ULONG val;

   } eTor;

} t_sommetAscenseur;

#endif // ASCPDEF_H
