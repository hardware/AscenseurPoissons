#ifndef TYPESINTERFACELOGICIELLE_H
#define TYPESINTERFACELOGICIELLE_H

#define CAPTEURS_ID           (unsigned long) 0x290
#define ENTREESTOR_COFFRET_ID (unsigned long) 0x190
#define SORTIESTOR_COFFRET_ID (unsigned long) 0x210
#define ENTREESTOR_SOMMET_ID  (unsigned long) 0x200
#define SORTIESTOR_SOMMET_ID  (unsigned long) 0x220

typedef unsigned short WORD;
typedef unsigned char uchar;
typedef unsigned long ULONG;

typedef struct
{

    union sTor {
        struct {
            uchar monteeGrille:1;
            uchar descenteGrille:1;
            uchar monteeVanne:1;
            uchar descenteVanne:1;
            uchar chauffageHuile:1;
            uchar demarragePompe:1;
            uchar bNC:2;
            uchar monteeCuve:1;
            uchar descenteCuve:1;
            uchar petiteVitesse:1;
            uchar GrandeVitesse:1;
            uchar marcheCentraleHydralique:1;
        };

        WORD val;
    };

    union eTor {
        struct {
            uchar detectHautGrille:1;
            uchar detectBasGrille:1;
            uchar detectHautVanne:1;
            uchar detectBasVanne:1;
            uchar niveauBasPoire:1;
            uchar defautMouDeCable:1;
            uchar detecteurSurcharge:1;
            uchar bNC1:1;
            uchar premiereCameSelecteurCadence:1;
            uchar deuxiemeCameSelecteurCadence:1;
            uchar troisiemeCameSelecteurCadence:1;
            uchar cuveDetecteurHaut:1;
            uchar cuveDetecteurHautGVPV:1;
            uchar cuveDetecteurBasGVPV:1;
            uchar cuveDetecteurTresBas:1;
            uchar bNC2:1;
            uchar confirmationMarchePompe:1;
            uchar confirmationMonteeCuve:1;
            uchar confirmationDescenteCuve:1;
            uchar confirmationPetiteVitesse:1;
            uchar confirmationGrandeVitesse:1;
            uchar confirmationCentrale:1;
            uchar bNC3:1;
        };

        WORD val;
    };

    union eAnalogique {
        struct {
            ULONG niveauEauAval:16;
            ULONG niveauEauAmont:16;
        };

        ULONG val ;
    };

} CoffretPecheur;


typedef struct
{
    union sTor {
        struct {
            uchar voyantDefautTemperature:1;
            uchar voyantNiveauBasPoire:1;
            uchar voyantDefautCycle:1;
            uchar voyantDefautTreuil:1;
            uchar voyantDefautCentraleHydraulique:1;
            uchar voyantDefautPompeAttrait:1;
            uchar compteurCycles:1;
            uchar DefautGeneral:1;
        };

        uchar val;
    };

    union eTor {
        struct {
            uchar BPArretUrgence:1;
            uchar BPMonteePV:1;
            uchar BPMonteeGV:1;
            uchar BPDescentePV:1;
            uchar BPDescenteGV:1;
            uchar BPMarcheCentraleHydraulique:1;
            uchar BPArretCentraleHydraulique:1;
            uchar bNC1:1;
            uchar marcheManuelle:1;
            uchar marcheAutomatique:1;
            uchar BPMonteeGrille:1;
            uchar BPDescenteGrille:1;
            uchar BPMonteeVanne:1;
            uchar BPDescenteVanne:1;
            uchar BPMarchePompe:1;
            uchar BPArretPompe:1;
            uchar BPCyclePecheur:1;
            uchar BPLancementCycleArmoire:1;
            uchar BPAcquittementDefaut:1;
            uchar ThermostatHuile:1;
            uchar NiveauBasHuile:1;
            uchar bNC2:3;
        };

      ULONG val;
   };



} SommetAscenseur ;



#endif // TYPESINTEMRFACELOGICIELLE_H
