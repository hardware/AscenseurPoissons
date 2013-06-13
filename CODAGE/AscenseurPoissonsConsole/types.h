#ifndef TYPES_H
#define TYPES_H

#include <QString>

// ##### INTERFACE LOGICIELLE ####

// Couleurs des voyants
const QString VERT = "border:3px solid rgb(125, 125, 125);\nbackground-color:green;";
const QString ORANGE = "border:3px solid rgb(125, 125, 125);\nbackground-color:orange;";
const QString ROUGE = "border:3px solid rgb(125, 125, 125);\nbackground-color: red;";
const QString GRIS = "border:3px solid rgb(125, 125, 125);\nbackground-color: rgb(63, 63, 63);";
const QString BLEU = "color: rgb(0, 0, 127);";

// Niveau d'alerte dans les logs
const QString INFO = "INFO";
const QString NOTICE = "NOTICE";
const QString WARNING = "WARNING";
const QString DEFAULT = "DEFAULT";
const QString ERR = "ERROR";
const QString CRITICAL = "CRITICAL";
const QString ALERT = "ALERT";
const QString EMERG = "EMERG";

const int PV_MAX = 100;
const int PV_MIN = 5;
const int PV_OFFSET = 5;

const int GV_MAX = 100;
const int GV_MIN = 5;
const int GV_OFFSET = 5;

// En minutes
const int TEMPS_PECHE_MAX = 360;
const int TEMPS_PECHE_MIN = 30;
const int TEMPS_PECHE_OFFSET = 30;

// En secondes
const int TEMPS_VIDANGE_MAX = 60;
const int TEMPS_VIDANGE_MIN = 10;
const int TEMPS_VIDANGE_OFFSET = 10;

const int NOMBRE_CYCLE_MAX = 1000;
const int NOMBRE_CYCLE_MIN = 1;
const int NOMBRE_CYCLE_OFFSET = 1;

// En heure
const int PERIODICITE_MAX = 24;
const int PERIODICITE_MIN = 1;
const int PERIODICITE_OFFSET = 1;

// ##### INTERFACE MATERIEL ####



#endif // TYPES_H
