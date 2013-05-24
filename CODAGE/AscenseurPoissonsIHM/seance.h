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


     Pompe *pPompe;
     CentraleHydraulique *pCentrale;
     VanneAttrait *pVanneAttrait;
     CageAscenseur *pCageAscenseur;
     Grille *pGrille;
     Capteurs *pCapteurs;


     int PV, GV, tempsPeche, tempsVidange, nbCycles, periodicite;
     QSettings *params;
     InterfaceCAN iCan;

public:

    Seance();
    ~Seance();

    void setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite);
    bool enregistrer();

};

#endif // SEANCE_H
