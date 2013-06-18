#ifndef TYPES_H
#define TYPES_H

#include <QString>

#define PV_MAX    100
#define PV_MIN    5
#define PV_OFFSET 5

#define GV_MAX    100
#define GV_MIN    5
#define GV_OFFSET 5

#define TEMPS_PECHE_MAX    360
#define TEMPS_PECHE_MIN    30
#define TEMPS_PECHE_OFFSET 30

#define TEMPS_VIDANGE_MAX    60
#define TEMPS_VIDANGE_MIN    10
#define TEMPS_VIDANGE_OFFSET 10

#define NOMBRE_CYCLE_MAX    1000
#define NOMBRE_CYCLE_MIN    1
#define NOMBRE_CYCLE_OFFSET 1

#define PERIODICITE_MAX    24
#define PERIODICITE_MIN    1
#define PERIODICITE_OFFSET 1

typedef enum {
    _DEM_POMPE      = 0,
    _ARRET_POMPE    = 1,
    _OUVRIR_VANNE   = 2,
    _FERMER_VANNE   = 3,
    _MONTER_CAGE    = 4,
    _DESCENDRE_CAGE = 5,
    _OUVRIR_GRILLE  = 6,
    _FERMER_GRILLE  = 7,
    _DEM_CENTRALE   = 8,
    _ARRET_CENTRALE = 9
} t_TypeTest;

typedef enum {
    _MANU       = 0,
    _AUTO_PAUSE = 1,
    _AUTO_RUN   = 2,
    _AUTO_BREAK = 3
} t_EtatSeance;

typedef enum {
    EVENT_INFO     = 0,
    EVENT_NOTICE   = 1,
    EVENT_WARNING  = 2,
    EVENT_DEFAULT  = 3,
    EVENT_ERR      = 4,
    EVENT_CRITICAL = 5,
    EVENT_ALERT    = 6,
    EVENT_EMERG    = 7
} t_NiveauEvenement;

// Couleurs des voyants
const QString VERT   = "border:3px solid rgb(125, 125, 125);\nbackground-color: green;";
const QString ORANGE = "border:3px solid rgb(125, 125, 125);\nbackground-color: orange;";
const QString ROUGE  = "border:3px solid rgb(125, 125, 125);\nbackground-color: red;";
const QString GRIS   = "border:3px solid rgb(125, 125, 125);\nbackground-color: rgb(63, 63, 63);";
const QString BLEU   = "color: rgb(0, 0, 127);";

// Niveau d'alerte dans les logs
const QString INFO = "INFO";
const QString NOTICE = "NOTICE";
const QString WARNING = "WARNING";
const QString DEFAULT = "DEFAULT";
const QString ERR = "ERROR";
const QString CRITICAL = "CRITICAL";
const QString ALERT = "ALERT";
const QString EMERG = "EMERG";


#endif // TYPES_H
