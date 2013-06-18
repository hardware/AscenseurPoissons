#ifndef SEANCE_H
#define SEANCE_H

#include "interfacecan.h"
#include "interfacecandlg.h"
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
    QSettings *params;

    Pompe *pPompe;
    CentraleHydraulique *pCentrale;
    VanneAttrait *pVanneAttrait;
    CageAscenseur *pCageAscenseur;
    Grille *pGrille;
    Capteurs *pCapteurs;

    InterfaceCAN iCan;
    InterfaceCANDlg *pIcan;

    t_EtatSeance etatSeance;

    int PV, GV, tempsPeche, tempsVidange, nbCycles, periodicite;

public:

    Seance();
    ~Seance();

    void setSeance(int PV, int GV, int tempsPeche, int tempsVidange, int nbCycles, int periodicite);
    bool enregistrer();
    void testerAppareillages(t_TypeTest type);
    void setEtatSeance(t_EtatSeance etatSeance);

};

#endif // SEANCE_H
