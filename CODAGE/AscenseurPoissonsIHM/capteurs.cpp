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

float Capteurs::LireCapteurTemperature()
{
    return 0;
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

float Capteurs::LireCapteurPositionAscenseurHaute()
{
    return 0;
}

float Capteurs::LireCapteurPositionAscenseurBasse()
{
    return 0;
}

float Capteurs::LireCapteurPositionVanneHaute()
{
    return 0;
}

float Capteurs::LireCapteurPositionVanneBasse()
{
    return 0;
}

float Capteurs::LireCapteurPositionPoireBas()
{
    return 0;
}
