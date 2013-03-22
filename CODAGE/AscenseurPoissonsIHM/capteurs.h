#ifndef CAPTEURS_H
#define CAPTEURS_H

#include "interfacecan.h"

class Capteurs
{

    InterfaceCAN *pIcan;

public:

    Capteurs(InterfaceCAN *pIcan);

    bool LireCapteurSurcharge();
    bool LireCapteurMouDeCable();
    bool LireCapteurFinDeCourseGrilleHaut();
    bool LireCapteurFinDeCourseGrilleBas();

    float LireCapteurTemperature();
    float LireCapteurNiveauHuile();
    float LireCapteurNiveauCanalAval();
    float LireCapteurNiveauCanalAmont();
    float LireCapteurPositionAscenseurHaute();
    float LireCapteurPositionAscenseurBasse();
    float LireCapteurPositionVanneHaute();
    float LireCapteurPositionVanneBasse();
    float LireCapteurPositionPoireBas();
};

#endif // CAPTEURS_H
