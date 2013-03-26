#ifndef SEANCE_H
#define SEANCE_H

#include "interfacecan.h"
#include "pompe.h"
#include "centralehydraulique.h"
#include "vanneattrait.h"
#include "cageascenseur.h"
#include "grille.h"
#include "capteurs.h"

#include <QApplication>
#include <QSettings>

class Seance
{
     InterfaceCAN iCan;

     Pompe *pPompe;
     CentraleHydraulique *pCentrale;
     VanneAttrait *pVanneAttrait;
     CageAscenseur *pCageAscenseur;
     Grille *pGrille;
     Capteurs *pCapteurs;

     QSettings *params;

     int PV, GV, tempsPeche, tempsVidange, nbCycles, periodicite;

public:

    Seance();
    ~Seance();

    void setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite);
    bool enregistrer();

};

#endif // SEANCE_H
