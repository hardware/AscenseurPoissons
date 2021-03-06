#ifndef CAPTEURS_H
#define CAPTEURS_H

#include "interfacecan.h"

/**
 * @class Capteurs
 * @brief Classe representant les capteurs
 */
class Capteurs
{
    /**
     * Pointeur contenant l'adresse d'une instance de la classe InterfaceCAN
     */
    InterfaceCAN *pIcan;

public:

    Capteurs(InterfaceCAN *pIcan);

    bool LireCapteurSurcharge();
    bool LireCapteurMouDeCable();
    bool LireCapteurFinDeCourseGrilleHaut();
    bool LireCapteurFinDeCourseGrilleBas();
    bool LireCapteurPositionAscenseurHaute();
    bool LireCapteurPositionAscenseurBasse();
    bool LireCapteurPositionVanneHaute();
    bool LireCapteurPositionVanneBasse();
    bool LireCapteurPositionPoireBas();
    bool LireConfirmationMarchePompe();
    bool LireDetecteurHautVanne();
    bool LireConfirmatioMarcheCentrale();
    bool LireCapteurPosition();
    bool LireCapteurTemperature();

    float LireCapteurNiveauHuile();
    float LireCapteurNiveauCanalAval();
    float LireCapteurNiveauCanalAmont();


};

#endif // CAPTEURS_H
