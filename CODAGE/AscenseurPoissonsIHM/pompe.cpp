#include "pompe.h"

Pompe::Pompe(InterfaceCAN *pIcan, Capteurs *pCapteurs)
{
    this->pIcan = pIcan;
    this->pCapteurs = pCapteurs;
}

void Pompe::demarrer()
{

}

bool Pompe::detecterArret()
{
    return true;
}
