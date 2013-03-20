#include "seance.h"

Seance::Seance()
{
    pPompe = new Pompe(&iCan);
    pCentrale = new CentraleHydraulique(&iCan);
    pVanneAttrait = new VanneAttrait(&iCan);
    pCageAscenseur = new CageAscenseur(&iCan);
    pGrille = new Grille(&iCan);
    pCapteurs = new Capteurs(&iCan);
}

Seance::~Seance()
{
    delete pPompe;
    delete pCentrale;
    delete pVanneAttrait;
    delete pCageAscenseur;
    delete pGrille;
    delete pCapteurs;
}
