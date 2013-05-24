#include "capteurs.h"

Capteurs::Capteurs(InterfaceCAN *pIcan)
{
    this->pIcan = pIcan;
}

bool Capteurs::LireCapteurSurcharge()
{
    return 0;
}

bool Capteurs::LireCapteurMouDeCable()
{
    return 0;
}

bool Capteurs::LireCapteurFinDeCourseGrilleHaut()
{
    return 0;
}

bool Capteurs::LireCapteurFinDeCourseGrilleBas()
{
    return 0;
}

bool Capteurs::LireCapteurTemperature()
{
    return false;
}

float Capteurs::LireCapteurNiveauHuile()
{
    return 0;
}

float Capteurs::LireCapteurNiveauCanalAval()
{
    return 0;
}

float Capteurs::LireCapteurNiveauCanalAmont()
{
    return 0;
}

bool Capteurs::LireCapteurPositionAscenseurHaute()
{
    return false;
}

bool Capteurs::LireCapteurPositionAscenseurBasse()
{
    return false;
}

bool Capteurs::LireCapteurPositionVanneHaute()
{
    return false;
}

bool Capteurs::LireCapteurPositionVanneBasse()
{
    return false;
}

bool Capteurs::LireCapteurPositionPoireBas()
{
    return false;
}

bool Capteurs::LireConfirmationMarchePompe()
{
    return false;
}

bool Capteurs::LireDetecteurHautVanne()
{
   return false;
}

bool Capteurs::LireConfirmatioMarcheCentrale()
{
    return false;
}
