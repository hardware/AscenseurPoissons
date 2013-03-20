#ifndef SEANCE_H
#define SEANCE_H

#include "interfacecan.h"
#include "pompe.h"
#include "centralehydraulique.h"
#include "vanneattrait.h"
#include "cageascenseur.h"
#include "grille.h"
#include "capteurs.h"

class Seance
{
     InterfaceCAN iCan;

     Pompe *pPompe;
     CentraleHydraulique *pCentrale;
     VanneAttrait *pVanneAttrait;
     CageAscenseur *pCageAscenseur;
     Grille *pGrille;
     Capteurs *pCapteurs;

public:

    Seance();
    ~Seance();

};

#endif // SEANCE_H
