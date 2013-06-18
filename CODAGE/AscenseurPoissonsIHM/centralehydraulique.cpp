#include "centralehydraulique.h"

CentraleHydraulique::CentraleHydraulique(InterfaceCAN *pIcan, Capteurs *pCapteurs)
{
    this->pIcan = pIcan;
    this->pCapteurs = pCapteurs;
}

void CentraleHydraulique::demarrer()
{

}

void CentraleHydraulique::arreter()
{

}
